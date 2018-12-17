#ifndef GRAPHDATAMODEL_H
#define GRAPHDATAMODEL_H

#include <QObject>
#include "recoderdata.h"
#include <QQueue>
#include <QList>
#include <QTime>
#include "adc.h"

class GraphDataModel: public QObject
{
    Q_OBJECT
public:
    explicit GraphDataModel(size_t size, QObject *parent = 0);
    ~GraphDataModel();
    RecoderData* channel(int ch);
    QTime getTime() const;

signals:
    void dataRecieved(float*,unsigned int);

public slots:
    void updateData(float*,unsigned int);
    void reset();

private:
    QList<RecoderData*> channels;
    QQueue<float*> dataSlots;
    QQueue<QTime> timeSlots;
    QTimer *tmr;
};

#endif // GRAPHDATAMODEL_H
