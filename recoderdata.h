#ifndef RECODERDATA_H
#define RECODERDATA_H

#include <QObject>
#include <qwt_series_data.h>


class RecoderData : public QwtSeriesData<QPointF>
{
public:
    RecoderData(QList<float*> *value,size_t size);
    ~RecoderData();
    size_t size() const;
    QPointF sample(size_t i) const;
    QRectF boundingRect() const;
    int chanell() const;
    void setChanell(int chanell);

private:
    QList<float *> *m_blockSlots;
    size_t m_size;
    int m_chanell;
};

#endif // RECODERDATA_H
