#include "recoderdata.h"
#include "adc.h"

RecoderData::RecoderData(QList<float *> *value,size_t size) : m_chanell(0)
{
    m_blockSlots = value;
    m_size = size;
}

RecoderData::~RecoderData()
{
}

size_t RecoderData::size() const
{
    Q_CHECK_PTR(m_blockSlots);
    return m_blockSlots->size() * (ADC_BLOCK_SIZE/ADC_CHANNEL_COUNT);
}

QPointF RecoderData::sample(size_t i) const
{
    // smaple(0...6399)
    // calc slot number
    int calcslot = i / (ADC_BLOCK_SIZE/ADC_CHANNEL_COUNT);
    int calcsample = i % (ADC_BLOCK_SIZE/ADC_CHANNEL_COUNT);
    Q_CHECK_PTR(m_blockSlots);
    if(!(calcslot < m_blockSlots->size()))
        return QPointF(i,0);
    float* data = m_blockSlots->at(calcslot);
    Q_CHECK_PTR(data);
    float val = data[(calcsample * 16) + m_chanell];
    return QPointF(i,val);
}

QRectF RecoderData::boundingRect() const
{
    return QRectF(0,0,m_size,10);
}

int RecoderData::chanell() const
{
    return m_chanell;
}

void RecoderData::setChanell(int chanell)
{
    if(chanell < 0 || chanell > (ADC_CHANNEL_COUNT-1))
        return;
    m_chanell = chanell;
}
