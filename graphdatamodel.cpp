#include "graphdatamodel.h"
#include "adc.h"

GraphDataModel::GraphDataModel(size_t size,QObject *parent) : QObject(parent)
{
    RecoderData* rd;
    for (int i = 0; i < ADC_CHANNEL_COUNT; i++){
        // recorder data on 6400 counts
        rd = new RecoderData(&dataSlots, size);
        rd->setChanell(i);
        channels.append(rd);
    }
}

GraphDataModel::~GraphDataModel()
{
    for (int i = 0; i < channels.length(); i++)
        free(channels.at(i));
    for (int i = 0; i < dataSlots.length(); i++) {
        Q_CHECK_PTR(dataSlots.head());
        free(dataSlots.dequeue());
    }
}

RecoderData* GraphDataModel::channel(int ch)
{
    if (ch >= 0 && ch <= channels.length())
        return channels.at(ch);
    else
        return NULL;
}


// update data from adc
// *data    float data[10240]
// size 10240
void GraphDataModel::updateData(float *data, unsigned int size)
{
    //qDebug()<< QString::number(size);
    float* mydata;
    mydata = (float*) malloc(size * sizeof(float));
    memcpy(mydata,data,size* sizeof(float));
    // in data slot 640 samples 16
    dataSlots.enqueue(mydata);
    timeSlots.enqueue(QTime::currentTime());
    if (dataSlots.size()>10) {
        timeSlots.dequeue();
        float* olddata = dataSlots.dequeue();
        Q_CHECK_PTR(olddata);
        free(olddata);
    }
    emit dataRecieved(mydata,size);
}

void GraphDataModel::reset()
{
    timeSlots.clear();
    for (int i = 0; i < dataSlots.length(); i++) {
        Q_CHECK_PTR(dataSlots.head());
        free(dataSlots.dequeue());
    }
    dataSlots.clear();
}

QTime GraphDataModel::getTime() const
{
    return timeSlots.at(0);
}
