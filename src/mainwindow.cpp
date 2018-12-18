#include "mainwindow.h"

#include "ui_mainwindow.h"
#include "adc.h"
#include <QtGui>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),saveOnExit(true),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->en_ch_10->setVisible(false);
    ui->tb_ch10->setVisible(false);
    ui->pv_label_10->setVisible(false);
    ui->lineEdit_10->setVisible(false);

    // Clock in status bar
    tmr500 = new QTimer(this);
    tmr500->start(500);
    connect(tmr500,SIGNAL(timeout()),SLOT(timeUpdate()));
    clock = new QLabel(ui->statusBar);
    ui->statusBar->addPermanentWidget(clock);

    // main crusher object
    crush = Crusher::instance();
    if (crush->isError())
    {
        QMessageBox::information(this,"Аппаратная ошибка",crush->getLastError(),QMessageBox::Ok);
    }
    connect(crush,SIGNAL(statusChanged(QString)),SLOT(showStatus(QString)));

    connect(ui->tb_filename,SIGNAL(textChanged(QString)),crush,SLOT(setFileprefix(QString)));
    connect(ui->bt_rec,SIGNAL(clicked()),crush,SLOT(rec()));
    connect(ui->bt_run,SIGNAL(clicked()),crush,SLOT(run()));
    connect(ui->bt_stop,SIGNAL(clicked()),crush,SLOT(stop()));

    dataModel = new GraphDataModel((ADC_BLOCK_SIZE/ADC_CHANNEL_COUNT)*10);

    // update crusher status on mode changed
    connect(crush,SIGNAL(modeChanged(Crusher::mode)),SLOT(sl_modeChanged(Crusher::mode)));
    // update dataModel on recive data from recorder
    connect(crush,SIGNAL(dataChanged(float*,unsigned int)),dataModel,SLOT(updateData(float*,unsigned int)));

    connect(dataModel,SIGNAL(dataRecieved(float*,unsigned int)),SLOT(sl_dataUpdate(float*,unsigned int)));

    // plot
    plot = new QwtPlot(this);
    ui->gb_plot->layout()->addWidget(plot);
    grid = new QwtPlotGrid();
    grid->enableXMin(true);
    grid->setMajorPen(QPen(Qt::black,0,Qt::DotLine));
    grid->setMinorPen(QPen(Qt::gray,0,Qt::DotLine));
    grid->attach(plot);

    curv[0] = new QwtPlotCurve(QString(trUtf8("Тензо 1")));
    curv[0]->setRenderHint(QwtPlotItem::RenderAntialiased);
    curv[0]->setPen(QPen(Qt::red));
    curv[1] = new QwtPlotCurve(QString(trUtf8("Тензо 2")));
    curv[1]->setRenderHint(QwtPlotItem::RenderAntialiased);
    curv[1]->setPen(QPen(Qt::darkRed));
    curv[2] = new QwtPlotCurve(QString(trUtf8("Скорость ПЧ1")));
    curv[2]->setRenderHint(QwtPlotItem::RenderAntialiased);
    curv[2]->setPen(QPen(Qt::yellow));
    curv[3] = new QwtPlotCurve(QString(trUtf8("Скорость ПЧ2")));
    curv[3]->setRenderHint(QwtPlotItem::RenderAntialiased);
    curv[3]->setPen(QPen(Qt::darkYellow));
    curv[4] = new QwtPlotCurve(QString(trUtf8("Момент ПЧ1")));
    curv[4]->setRenderHint(QwtPlotItem::RenderAntialiased);
    curv[4]->setPen(QPen(Qt::green));
    curv[5] = new QwtPlotCurve(QString(trUtf8("Момент ПЧ2")));
    curv[5]->setRenderHint(QwtPlotItem::RenderAntialiased);
    curv[5]->setPen(QPen(Qt::darkGreen));
    curv[6] = new QwtPlotCurve(QString(trUtf8("Ток ПЧ1")));
    curv[6]->setRenderHint(QwtPlotItem::RenderAntialiased);
    curv[6]->setPen(QPen(Qt::blue));
    curv[7] = new QwtPlotCurve(QString(trUtf8("Ток ПЧ2")));
    curv[7]->setRenderHint(QwtPlotItem::RenderAntialiased);
    curv[7]->setPen(QPen(Qt::darkBlue));
    curv[8] = new QwtPlotCurve(QString(trUtf8("Угол 1")));
    curv[8]->setRenderHint(QwtPlotItem::RenderAntialiased);
    curv[8]->setPen(QPen(0x55aaff));
    //curv[9] = new QwtPlotCurve(QString(trUtf8("Угол 2")));
    //curv[9]->setRenderHint(QwtPlotItem::RenderAntialiased);
   // curv[9]->setPen(QPen(Qt::black));
    
    timescale = new TimeScaleDraw(QTime::currentTime());
    plot->setAxisScaleDraw(QwtPlot::xBottom,timescale);
    curv[0]->setData(dataModel->channel(0));
    curv[0]->attach(plot);
    curv[1]->setData(dataModel->channel(1));
    curv[1]->attach(plot);
    curv[2]->setData(dataModel->channel(2));
    curv[2]->attach(plot);
    curv[3]->setData(dataModel->channel(3));
    curv[3]->attach(plot);
    curv[4]->setData(dataModel->channel(4));
    curv[4]->attach(plot);
    curv[5]->setData(dataModel->channel(5));
    curv[5]->attach(plot);
    curv[6]->setData(dataModel->channel(6));
    curv[6]->attach(plot);
    curv[7]->setData(dataModel->channel(7));
    curv[7]->attach(plot);
    curv[8]->setData(dataModel->channel(8));
    curv[8]->attach(plot);
    //curv[9]->setData(dataModel->channel(9));
    //curv[9]->attach(plot);
    
    plot->replot();

    connect(ui->en_ch_1,SIGNAL(clicked(bool)),SLOT(enableChannel(bool)));
    connect(ui->en_ch_2,SIGNAL(clicked(bool)),SLOT(enableChannel(bool)));
    connect(ui->en_ch_3,SIGNAL(clicked(bool)),SLOT(enableChannel(bool)));
    connect(ui->en_ch_4,SIGNAL(clicked(bool)),SLOT(enableChannel(bool)));
    connect(ui->en_ch_5,SIGNAL(clicked(bool)),SLOT(enableChannel(bool)));
    connect(ui->en_ch_6,SIGNAL(clicked(bool)),SLOT(enableChannel(bool)));
    connect(ui->en_ch_7,SIGNAL(clicked(bool)),SLOT(enableChannel(bool)));
    connect(ui->en_ch_8,SIGNAL(clicked(bool)),SLOT(enableChannel(bool)));
    connect(ui->en_ch_9,SIGNAL(clicked(bool)),SLOT(enableChannel(bool)));
    connect(ui->en_ch_10,SIGNAL(clicked(bool)),SLOT(enableChannel(bool)));

    ui->lb_rectime->setVisible(false);
  //  setWindowFlags(Qt::CustomizeWindowHint  | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);


    conv = new CSV(this);
    connect(conv,SIGNAL(progressChanged(int)),SLOT(sl_convprogress(int)));


    loadSettings();
    setWindowState(Qt::WindowFullScreen);
}



void MainWindow::enableChannel(bool en)
{
    QCheckBox* cb = qobject_cast<QCheckBox*>(sender());
    if (cb != NULL) {
        bool ok;
        int num = cb->objectName().right(1).toInt(&ok);
        if (ok)
            curv[num - 1]->setVisible(en);
        plot->replot();
    }
}

// *************************  MainForm  *************************************
void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, trUtf8("Завершение работы"), trUtf8("Вы уверены?"),
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::No) {
        event->ignore();
    } else {
        if (saveOnExit) {
            saveSettings();
            crush->saveParameters();
        }
        event->accept();
    }
}

void MainWindow::saveSettings()
{
//   ParamSaver::save(tr("Filter"),tr("alpha"),QVariant( ui->tb_filtr->text()));
//   ParamSaver::save(tr("Channels"),tr("Visible_1"),QVariant( ui->en_ch_1->isChecked()));
//   ParamSaver::save(tr("Channels"),tr("Visible_2"),QVariant( ui->en_ch_2->isChecked()));
//   ParamSaver::save(tr("Channels"),tr("Visible_3"),QVariant( ui->en_ch_3->isChecked()));
//   ParamSaver::save(tr("Channels"),tr("Visible_4"),QVariant( ui->en_ch_4->isChecked()));
//   ParamSaver::save(tr("Channels"),tr("Visible_5"),QVariant( ui->en_ch_5->isChecked()));
//   ParamSaver::save(tr("Channels"),tr("Visible_6"),QVariant( ui->en_ch_6->isChecked()));
//   ParamSaver::save(tr("Channels"),tr("Visible_7"),QVariant( ui->en_ch_7->isChecked()));
//   ParamSaver::save(tr("Channels"),tr("Visible_8"),QVariant( ui->en_ch_8->isChecked()));
}

void MainWindow::loadSettings()
{
    ui->pv_label_1->setText(crush->getParameters()->data(crush->getParameters()->index(0,PARAM_NAME)).toString());
    ui->pv_label_2->setText(crush->getParameters()->data(crush->getParameters()->index(1,PARAM_NAME)).toString());
    ui->pv_label_3->setText(crush->getParameters()->data(crush->getParameters()->index(2,PARAM_NAME)).toString());
    ui->pv_label_4->setText(crush->getParameters()->data(crush->getParameters()->index(3,PARAM_NAME)).toString());
    ui->pv_label_5->setText(crush->getParameters()->data(crush->getParameters()->index(4,PARAM_NAME)).toString());
    ui->pv_label_6->setText(crush->getParameters()->data(crush->getParameters()->index(5,PARAM_NAME)).toString());
    ui->pv_label_7->setText(crush->getParameters()->data(crush->getParameters()->index(6,PARAM_NAME)).toString());
    ui->pv_label_8->setText(crush->getParameters()->data(crush->getParameters()->index(7,PARAM_NAME)).toString());
    ui->pv_label_9->setText(crush->getParameters()->data(crush->getParameters()->index(8,PARAM_NAME)).toString());
    ui->pv_label_10->setText(crush->getParameters()->data(crush->getParameters()->index(9,PARAM_NAME)).toString());
}

MainWindow::~MainWindow()
{
    int i;
    delete ui;
    delete grid;
    for (i = 0; i < 10; i++) {
        Q_CHECK_PTR(curv[i]);
        delete curv[i];
    }
    delete crush;
}

void MainWindow::sl_modeChanged(Crusher::mode mode)
{
    QFile defaultfile(QApplication::applicationDirPath() + "/default.sreccfg");
    switch(mode) {
    case Crusher::Stop:
        qDebug()<<"PWD - " + QApplication::applicationDirPath();
        showStatus("Конец записи в файл.");
        ui->bt_rec->setEnabled(true);
        dataModel->reset();
        plot->replot();
        ui->lb_rectime->setVisible(false);
        if (defaultfile.exists()) {
            showStatus("Запись файла конфигурации " + crush->filename() + ".sreccfg");
            QFile::copy(QApplication::applicationDirPath() + "/default.sreccfg", crush->fullFilename()+ ".sreccfg");
        }
        showStatus("Экспорт в формат CSV");
        QApplication::processEvents();
        int i;
        for(i = 0; i < crush->getParameters()->rowCount(QModelIndex()); i++) {
            conv->setEnable(crush->getParameters()->index(i,PARAM_ENABLE).data().toString()==trUtf8("Включен"),i+1);
            conv->setName(crush->getParameters()->index(i,PARAM_NAME).data().toString(),i+1);
            conv->setKoef(crush->getParameters()->index(i,PARAM_KOEF).data().toFloat(),i+1);
            conv->setOffs(crush->getParameters()->index(i,PARAM_OFFSET).data().toFloat(),i+1);
        }
        if (!conv->convert("./" + crush->fullFilename()+".alf")) {
            showStatus("");
            showStatus("Экспорт CSV завершен");
        } else {
            showStatus("Ошибка при экспорте CSV");
        }
        break;
    case Crusher::Run:
        ui->tb_info->clear();
        timescale = new TimeScaleDraw(QTime::currentTime());
        plot->setAxisScaleDraw(QwtPlot::xBottom,timescale);
        plot->replot();
        showStatus("Процесс сбора данных.");
        ui->bt_run->setEnabled(false);
        ui->bt_savefile->setEnabled(false);
        ui->bt_stop->setEnabled(true);
        ui->bt_rec->setEnabled(true);
        break;
    case Crusher::Sim:
        ui->tb_info->clear();
        timescale = new TimeScaleDraw(QTime::currentTime());
        plot->setAxisScaleDraw(QwtPlot::xBottom,timescale);
        plot->replot();
        showStatus("Имитация сбора данных.");
        ui->bt_run->setEnabled(false);
        ui->bt_savefile->setEnabled(false);
        ui->bt_stop->setEnabled(true);
        ui->bt_rec->setEnabled(true);
        break;
    case Crusher::Rec:
        showStatus(QString("Запись данных в файл " + crush->filename() + ".alf"));
        ui->bt_rec->setEnabled(false);
        tm.start();
        ui->lb_rectime->setText("");
        ui->lb_rectime->setVisible(true);
        break;
    case Crusher::End:
        showStatus("Cбор данных завершен.");
        ui->bt_run->setEnabled(true);
        ui->bt_savefile->setEnabled(true);
        ui->bt_stop->setEnabled(false);
        ui->bt_rec->setEnabled(false);
        ui->tb_ch1->setText("----");
        ui->tb_ch2->setText("----");
        ui->tb_ch3->setText("----");
        ui->tb_ch4->setText("----");
        ui->tb_ch5->setText("----");
        ui->tb_ch6->setText("----");
        ui->tb_ch7->setText("----");
        ui->tb_ch8->setText("----");
        ui->tb_ch9->setText("----");
        ui->tb_ch10->setText("----");
        dataModel->reset();
        plot->replot();
        break;
    }
}

void MainWindow::sl_convprogress(int progress)
{
   if (progress % 10 == 0) {
       ui->tb_info->setPlainText(ui->tb_info->toPlainText() + ".");
       QApplication::processEvents();
   }
}

void MainWindow::timeUpdate()
{
    // update datetime
    clock->setText(QDateTime::currentDateTime().toString("dddd dd/MM/yyyy HH:mm:ss"));
    // update record time
    if (crush->isRec()) {
        QTime nn;
        int ms = tm.elapsed();
        nn =QTime(0,0,0).addMSecs(ms);
        QString recordtime = nn.toString();
        ui->lb_rectime->setText(recordtime);
    }
}

void MainWindow::showStatus(const QString &msg)
{
    ui->tb_info->setPlainText(ui->tb_info->toPlainText() + msg + "\n");
}

float MainWindow::getAbsoluteData(float *data,int channel)
{
    if (channel < 0 || channel >= ADC_CHANNEL_COUNT)
        return qSNaN();
    bool koef_ok,off_ok;
    float *dt = data + channel;
    float koef = crush->getParameters()->index(channel,PARAM_KOEF).data().toFloat(&koef_ok);
    float off = crush->getParameters()->index(channel,PARAM_OFFSET).data().toFloat(&off_ok);
    return (koef_ok && off_ok && *dt > -10.0) ? koef * (*dt - off): qSNaN();
 }

void MainWindow::sl_dataUpdate(float *data, size_t size)
{
    if (size > 16 && (crush->isRun() || crush->isRec())) {
        for (int i = 0; i < 10; i++) {
            float val= getAbsoluteData(data,i);
            QLineEdit *obj = ui->gb_actualData->findChild<QLineEdit*>("tb_ch"+QString::number(i+1));
            if (obj != NULL)
                obj->setText(val == val ? QString::number(val,'f',3):"----");
        }
        timescale = new TimeScaleDraw(dataModel->getTime());
        plot->setAxisScaleDraw(QwtPlot::xBottom,timescale);
        plot->replot();
    }
}

void MainWindow::on_tb_filtr_textChanged(const QString &arg1)
{
//    bool ok;
//    float alpha = arg1.toFloat(&ok);
//    if(ok && alpha>=0 && alpha<=1)
//    {
//        crush->setFilterAlpha(alpha);
//        ui->horizontalSlider->setValue(alpha*1000);
//    }
//    else
//    {
//        ui->tb_filtr->setText(QString::number(crush->filterAlpha(),'g',3));
//        ui->horizontalSlider->setValue(crush->filterAlpha()*1000);
//    }
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
//    float val = value;
//    val/=1000;
//    crush->setFilterAlpha(val);
//  //  ui->tb_filtr->setText(QString::number(crush->filterAlpha(),'g',3));
}

void MainWindow::on_bt_savefile_clicked()
{
    FileCopyDialog copyfile;
    copyfile.setModal(true);
    copyfile.exec();
}

void MainWindow::on_act_aboutQt_triggered()
{
    QApplication::aboutQt();
}

void MainWindow::on_act_koef_triggered()
{
    SetupKoefDialog *koef = new SetupKoefDialog(crush->getParameters(),this);
    koef->setAttribute(Qt::WA_DeleteOnClose);
    koef->setModal(true);
    if (QDialog::Accepted == koef->exec()) {
        crush->saveParameters();
        loadSettings();
    }
}

void MainWindow::on_bt_keyb_clicked()
{
    QProcess::startDetached("osk.exe");
}

void MainWindow::on_act_about_triggered()
{
    QMessageBox::information(this,tr("О программе"),tr("ПО Экспериментальной дробилки\nВерсия 1.03.01"));
}

void MainWindow::on_actionTeamViewer_triggered()
{
    QProcess::startDetached("D:/TeamViewer/TeamViewer.exe");
}
