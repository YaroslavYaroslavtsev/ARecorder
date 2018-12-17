#ifndef CRUSHER_H
#define CRUSHER_H

#include <QObject>
#include "adc.h"
#include "ADCsdk/alf.h"
#include <QDir>
#include <QFile>
#include <QDateTime>
#include <QtCore/qmath.h>
#include "parammodel.h"
#include "paramsaver.h"
#include "expfilter.h"

class Crusher : public QObject
{
    Q_OBJECT
    Q_ENUMS(mode)
public:
    enum mode{
        Stop = 0,
        Run,
        Rec,
        Sim,
        End
    };

    static Crusher* instance();
    ~Crusher();

    void emitDataChanged(float*,unsigned int);
    void execCmd(QString&,void*);
    int init();
    QString getLastError() const;
    QString fileprefix();
    QString filename();
    QString fullFilename();
    void setFilterAlpha(float,int);
    float filterAlpha(int);
    bool isRun();
    bool isRec();
    bool isSim();
    bool isError();
    ParamModel *getParameters() const;
    void saveParameters();
    void loadParameters();
    void applyParameters();

signals:
    void dataRecived(float*,unsigned int);
    void dataChanged(float*,unsigned int);
    void modeChanged(Crusher::mode);
    void statusChanged(const QString&);

public slots:
    void rec();
    void stop();
    void run();
    void setFileprefix(QString);

private slots:
    void simulateData();
    void filterComplete(float*,unsigned int);

private:
    explicit Crusher(QObject *parent = 0);
    static  Crusher *classAddress;
    ADC *adc;
    ParamModel *m_parameters;
    ExpFilter *filter;
    HANDLE m_hFile ;
    QString m_prefix; // user prefix
    QString m_filename; // fullname prefx+datetime
    bool m_run;
    bool m_rec;
    bool m_simul;
    int lastError;
    QFile file;
    QTimer *simulator;
    float *simdata;
    float sim_val;
};

#endif // CRUSHER_H
