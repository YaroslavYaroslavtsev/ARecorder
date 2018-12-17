#include "expfilter.h"

ExpFilter::ExpFilter(int channel, QObject *parent) : QObject(parent),m_channel(channel)
{
    int i;
    m_tmp = (float*)malloc(m_channel * sizeof(float));
    m_alpha = (float*)malloc(m_channel * sizeof(float));
    for (i = 0; i < m_channel; i++)
        m_alpha[i] = 1.0;
    reset();
}

ExpFilter::~ExpFilter()
{
    free(m_tmp);
    free(m_alpha);
}

void ExpFilter::filter(float *data, unsigned int len)
{
    if(len % m_channel > 0) return;
    int samples = len / m_channel / sizeof(float);
    for (int j = 0; j < samples; j++) {
        for(int i = 0; i < m_channel; i++) {
            float newdata;
            int ptr = j * m_channel + i ;
            newdata = m_tmp[i] + (data[ptr] - m_tmp[i]) * m_alpha[i];
            m_tmp[i] = newdata;
            data[ptr] = newdata;
        }
    }
    emit dataChanged(data,len);
}

void ExpFilter::reset()
{
    for(int i = 0; i < m_channel; i++)
        m_tmp[i] = 0.0;
}

float ExpFilter::alpha(int ch) const
{
    return m_alpha[ch];
}

void ExpFilter::setAlpha(float alpha, int ch)
{
    if (alpha < 0 || alpha > 1 || ch < 0 || ch >= m_channel)
        return;
    m_alpha[ch] = alpha;
}
