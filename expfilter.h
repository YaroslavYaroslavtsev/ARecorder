#ifndef EXPFILTER_H
#define EXPFILTER_H

#include <QObject>

class ExpFilter: public QObject
{
    Q_OBJECT
public:
    ExpFilter(int channel, QObject *parent = 0);
    ~ExpFilter();
    float alpha(int ch = 0) const;
    void setAlpha(float alpha,int ch = 0);

signals:
    void dataChanged(float*,unsigned int);

public slots:
    void filter(float*,unsigned int);
    void reset();

private:
    float *m_alpha;
    int m_channel;
    float *m_tmp;
};

#endif // EXPFILTER_H
