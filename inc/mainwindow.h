#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "crusher.h"
#include "setupkoefdialog.h"
#include "csv.h"
#include <QLabel>
#include "filecopydialog.h"
#include "graphdatamodel.h"
#include <qwt_plot.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_curve.h>
#include <qwt_scale_draw.h>
#include <timescaledraw.h>
#include <recoderdata.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void sl_convprogress(int);
    void sl_dataUpdate(float*,unsigned int);
    void enableChannel(bool);
    void sl_modeChanged(Crusher::mode);
    void timeUpdate(void);
    void showStatus(const QString&);
    void on_bt_keyb_clicked();
    void on_bt_savefile_clicked();
    void on_act_aboutQt_triggered();
    void on_act_koef_triggered();
    void on_tb_filtr_textChanged(const QString &arg1);
    void on_horizontalSlider_valueChanged(int value);
    void on_act_about_triggered();
    void on_actionTeamViewer_triggered();

private:
    void closeEvent(QCloseEvent*);
    void saveSettings();
    void loadSettings();
    float getAbsoluteData(float *data,int channel);

    Ui::MainWindow *ui;
    QTimer *tmr500;
    QLabel *clock;
    Crusher *crush;
    bool saveOnExit;
    CSV *conv;
    QTime tm;
    QwtPlot *plot;
    QwtPlotGrid *grid;
    QwtPlotCurve* curv[16];
    GraphDataModel *dataModel;
    TimeScaleDraw *timescale;
};

#endif // MAINWINDOW_H
