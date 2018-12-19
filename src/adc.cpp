#include "adc.h"
#include "ADCsdk/alf.h"
#include <QDebug>

ADC::ADC(QObject *parent) : QObject(parent),m_ready(0)
{
    //  Создаем фабрику для DLL потокового сбора ADC данных
    DllClient DClient;
    //  Именно то место, где нужно подставить правильное название устройства.
    //  Получаем интерфейс
    pADC = (IADCDevice*)DClient.LoadDriver("EL200E", "IADCDevice", 0);
}

ADC::~ADC()
{
   if(m_ready) {
        pADC->Stop();
        pADC->Release();
    }
}

int ADC::init(ADCParametersSTREAMCallBack cb)
{
    if(pADC == 0) {
        qDebug() << "ERROR - Object not created!";
        return ERR_LOAD;
    }

//  Номера устройств начинаются с 1. Захват устройства с номером 1.
    if(pADC->Setup(1, 0, 0, 0) <= 0) {
        qDebug() << "ERROR - Setup not ready!";
        return ERR_SETUP;
    }

    int result;
    for(int i = 0; i < ADC_CHANNEL_COUNT; i++) {
        Channels[i] =  i;
        Gains[i] = GAIN + (GAIN << 16);
    }
    m_chnum = ADC_CHANNEL_COUNT;

    //  Сбор потока данных с режимом сканирования каналов.
    //  Структура параметроы измерения

    ps.m_Block.m_nStartOf      = ADCPARAM_START_TIMER;          // источник запусков;
    ps.m_Block.m_nBlockSize    = ADC_BLOCK_SIZE;                      // размер блока данных;
    ps.m_Block.m_nMode         = ADC_BLOCK_MODE_MODECYCLE2;     // режим сбора циклический, в отдельном потоке.
    //ps.m_Block.m_nControl      = ADC_BLOCK_CONTROL_GAIN_PAIR;   // синхронные пары каналов;
    ps.m_Block.m_nControl      = ADC_BLOCK_CONTROL_MODEZERO;
    ps.m_Block.m_nLevel        = 0;                             // не применимо;
    ps.m_Block.m_fFreqStart    = FREQ_STREAM;                   // частота сбора данных
    ps.m_Block.m_fFreqPack     = 0.0;                           // не применимо;
    ps.m_Block.m_nChannelCount = m_chnum;
    ps.m_Block.m_pnGains       = Gains;
    ps.m_Block.m_pnChannels    = Channels;
    ps.m_pCallBack             = cb;                   // Вызывается из отдельного потока внутри драйвера
    // ps.m_vCallBackObj          = parent;                      // указатель на данные пользователя
    ps.m_vCallBackData         = mvolt;                         // Буфер данных
    ps.m_vCallBackMode         = ADC_DATA_MODE_CONVERT2FLOAT;
    ps.m_vCallBackSize         = DIM(mvolt);                    // Размер буфера данных

    //  Если возвращаемое значение больше 0, то все прошло учпешно.
    if(pADC != 0)
        result = pADC->Init(ADC_INIT_MODE_INIT, &ps, 0);
    if(result <= 0)
        return ERR_INIT;
    m_ready = true;
    return 0;
}

void ADC::start()
{
    if(!m_ready)
        return;

    pADC->Start();
}

void ADC::stop()
{
    if(!m_ready)
        return;
    pADC->Stop();
}

int ADC::getSerial()
{
    if(!m_ready)
        return 0;
    //  Получение серийного номера устройства
    unsigned serN = 0;
    pADC->Get(ADC_GET_SERIALNUMBER_LONG, &serN);
    return serN;
}

bool ADC::isReady()
{
    return m_ready;
}
