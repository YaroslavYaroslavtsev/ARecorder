#include "filecopydialog.h"
#include "ui_filecopydialog.h"
#include <QStorageInfo>
#include <QDebug>
#include <QApplication>
#include <QMessageBox>

FileCopyDialog::FileCopyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileCopyDialog)
{
    ui->setupUi(this);
    connect(ui->bt_refresh,SIGNAL(clicked()),SLOT(sl_update()));
    connect(ui->bt_delete,SIGNAL(clicked()),SLOT(sl_delete()));
    connect(ui->bt_copy,SIGNAL(clicked()),SLOT(sl_copy()));
    connect(ui->bt_alf,SIGNAL(clicked()),SLOT(sl_alf()));
    connect(ui->bt_csv,SIGNAL(clicked()),SLOT(sl_csv()));
    connect(ui->bt_dir,SIGNAL(clicked()),SLOT(sl_content()));

    msgBox = new QMessageBox(this);
    // Заголовок сообщения
    msgBox->setWindowTitle(trUtf8("Информация"));
    // Тип иконки сообщения
    msgBox->setIcon(QMessageBox::Information);
    // Основное сообщение Message Box
    // Добавление реагирования на софт клавиши
    msgBox->setStandardButtons(QMessageBox::Ok);

    setHideAddPanel(false);

    connect(ui->lv_disk,SIGNAL(clicked(QModelIndex)),SLOT(sl_diskChanged(QModelIndex)));

    csvfiles.append("*.csv");
    alffiles.append("*.alf");
    alfcfgfiles.append("*.alf");
    alfcfgfiles.append("*.sreccfg");

    dir = new QFileSystemModel(this);
    dir->setRootPath("./Excel/");
    dir->setNameFilters(csvfiles);
    dir->setNameFilterDisables(false);

    ui->lv_files->setModel(dir);
    ui->lv_files->setRootIndex(dir->index("./Excel/"));

    disk = new QFileSystemModel(this);
    disk->setRootPath(disk->myComputer().toString());
    ui->lv_disk->setModel(disk);
}

FileCopyDialog::~FileCopyDialog()
{
    delete ui;
}

void FileCopyDialog::sl_update()
{
    delete disk;
    disk = new QFileSystemModel(this);
    disk->setRootPath("");
    ui->lv_disk->setModel(disk);
}

void FileCopyDialog::sl_copy()
{
    if (ui->lv_files->selectionModel()->selectedIndexes().count() == 0) {
        QMessageBox::information(this,trUtf8("Информация"),trUtf8("Не выбран файл для копирования"),QMessageBox::Ok);
        return;
    }
    if (ui->lv_disk->selectionModel()->selectedIndexes().count() == 0) {
        QMessageBox::information(this,trUtf8("Информация"),trUtf8("Не выбран диск"),QMessageBox::Ok);
        return;
    }
    QString srcdir =  dir->rootPath() + "/";
    QString srcfile = ui->lv_files->selectionModel()->selectedIndexes().at(0).data(QFileSystemModel::FileNameRole).toString();
    QString dstdir = ui->lv_disk->selectionModel()->selectedIndexes().at(0).data(QFileSystemModel::FilePathRole).toString();
    QString cfgfile = srcfile.left(srcfile.length() - 4) + ".sreccfg";
    qDebug() << srcdir + srcfile;
    qDebug() << srcdir + cfgfile;
    qDebug() << dstdir + srcfile;
    if(QFile::exists(dstdir + srcfile) || QFile::exists(dstdir + cfgfile)) {
        int result = QMessageBox::question(this, trUtf8("Подтверждение"),trUtf8("Файл существует!Перезаписать?"),QMessageBox::Yes,QMessageBox::No);
        if (result == QMessageBox::No)
            return;
        if (!QFile::remove(dstdir + srcfile) && !QFile::remove(dstdir + cfgfile)) {
            QMessageBox::information(this,trUtf8("Информация"),trUtf8("Ошибка в процессе удаления"),QMessageBox::Ok);
            return;
        }
    }

    this->setCursor(QCursor(Qt::WaitCursor));
    if(QFile::copy(srcdir + srcfile, dstdir + srcfile) && (QFile::copy(srcdir + cfgfile, dstdir + cfgfile) || !QFile::exists(srcdir + cfgfile))) {
        this->setCursor(QCursor(Qt::ArrowCursor));
        QMessageBox::information(this,trUtf8("Информация"),trUtf8("Файл скопирован"),QMessageBox::Ok);
    } else {
        this->setCursor(QCursor(Qt::ArrowCursor));
        QMessageBox::information(this,trUtf8("Информация"),trUtf8("Ошибка в процессе копирования"),QMessageBox::Ok);
    }
}

void FileCopyDialog::sl_delete()
{
    if (ui->lv_files->selectionModel()->selectedIndexes().count() == 0) {
        QMessageBox::information(this,trUtf8("Информация"),trUtf8("Не выбран файл для удаления"),QMessageBox::Ok);
        return;
    }
    QString srcdir =  dir->rootPath() + "/";
    QString srcfile = ui->lv_files->selectionModel()->selectedIndexes().at(0).data(QFileSystemModel::FileNameRole).toString();
    QString cfgfile = srcfile.left(srcfile.length() - 4) + ".sreccfg";
    qDebug() << srcdir + srcfile;
    qDebug() << srcdir + cfgfile;
    int result;
    result = QMessageBox::question(this, trUtf8("Подтверждение"),trUtf8("Удалить файл?"),QMessageBox::Yes,QMessageBox::No);
    if (result == QMessageBox::No)
        return;
    if (QFile::remove(srcdir + srcfile)) {
        if (QFile::exists(srcdir + cfgfile))
            QFile::remove(srcdir + cfgfile);
        msgBox->setText(trUtf8("Файл удален"));
        msgBox->show();
    } else {
        msgBox->setText(trUtf8("Ошибка в процессе удаления"));
        msgBox->show();
    }
}

void FileCopyDialog::sl_csv()
{
    dir->setRootPath("./Excel/");
    dir->setNameFilters(csvfiles);
    ui->lv_files->setRootIndex(dir->index("./Excel/"));
}

void FileCopyDialog::sl_alf()
{
    dir->setRootPath("./Records/");
    dir->setNameFilters(alffiles);
    ui->lv_files->setRootIndex(dir->index("./Records/"));
}

void FileCopyDialog::sl_diskChanged(QModelIndex index)
{
    ui->bt_dir->setText("Просмотр диска " + index.data().toString());
    // cont->setRootPath(ui->lv_disk->selectedIndexes().at(0));
    ui->lv_content->setModel(disk);
    ui->lv_content->setRootIndex(ui->lv_disk->selectionModel()->selectedIndexes().at(0));
}

void FileCopyDialog::sl_content()
{
    setHideAddPanel(!isVisibleAddPanel());
}

void FileCopyDialog::sl_contentFilter()
{
     QPushButton* bt = qobject_cast<QPushButton*>(sender());
     if (bt != NULL) {
//    if(bt->objectName()=="bt_all") cont->setNameFilters(QStringList());
//    if(bt->objectName()=="bt_csv2") cont->setNameFilters(csvfiles);
//    if(bt->objectName()=="bt_alf2") cont->setNameFilters(alfcfgfiles);
     }
}

void FileCopyDialog::setHideAddPanel(bool hide)
{
    ui->lv_content->setVisible(hide);
    ui->bt_all->setVisible(false);
    ui->bt_csv_2->setVisible(false);
    ui->bt_alf_2->setVisible(false);
}

bool FileCopyDialog::isVisibleAddPanel()
{
    return  ui->lv_content->isVisible();
//    &&
//    ui->bt_all->isVisible()&&
//    ui->bt_csv->isVisible()&&
//    ui->bt_alf->isVisible();
}
