#ifndef ADC_H
#define ADC_H

#include "ADCsdk/IADCDevice.h"
#include "ADCsdk/DllClient.h"
#include <QObject>
#include <QTimer>

#define ADC_BLOCK_SIZE (1024*10)
#define ADC_CHANNEL_COUNT (16)
#define SLOT_SIZE (ADC_BLOCK_SIZE/ADC_CHANNEL_COUNT)

#define     GAIN    1   // вместо 1 можно поставить 1, 10, 100, 200
#define     FREQ_STREAM         32000.0

#define ERR_NONE 0
#define ERR_LOAD -1
#define ERR_SETUP -2
#define ERR_INIT -3
#define ERR_NODIR -4

class ADC: public QObject
{
    Q_OBJECT
public:
    explicit ADC(QObject *parent = 0);
    ~ADC();
   int init(ADCParametersSTREAMCallBack cb);
   void start();
   void stop();
   int getSerial();
   bool isReady();

private:
    IADCDevice* pADC;
    int m_chnum;
    int         Channels[ADC_CHANNEL_COUNT];
    int         Gains[ADC_CHANNEL_COUNT];
    float       mvolt[ADC_BLOCK_SIZE];
    bool m_ready;
    ADCParametersSTREAM ps;
};

int __stdcall  ADCCallBack(void* pObj, void*& pData, int size, int mode);
#endif // ADC_H
