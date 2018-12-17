#ifndef TIMESCALEDRAW_H
#define TIMESCALEDRAW_H

#include <QTime>

class TimeScaleDraw : public QwtScaleDraw
{
public:
    TimeScaleDraw(const QTime &base):
        baseTime(base) {
    }
    virtual QwtText label(double v) const {
        QTime upTime = baseTime.addMSecs((int)v * 0.5);
        return upTime.toString("HH.mm.ss\n    zzz");
    }

private:
    QTime baseTime;
};

#endif // TIMESCALEDRAW_H
