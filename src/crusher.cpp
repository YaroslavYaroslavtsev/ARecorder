#include "crusher.h"
#include <QDebug>

Crusher* Crusher::classAddress = NULL;

Crusher::Crusher(QObject *parent) : QObject(parent),m_run(false),m_rec(false),m_simul(true)
{
    // prepare ADC
    adc = new ADC(this);
    // exponential filter
     filter = new ExpFilter(16,this);
     connect(this,SIGNAL(dataRecived(float*,unsigned int)),filter,SLOT(filter(float*,unsigned int)));
     connect(filter,SIGNAL(dataChanged(float*,unsigned int)),SLOT(filterComplete(float*,uint)));

     //connect(this,SIGNAL(dataRecived(float*,unsigned int)),SLOT(filterComplete(float*,uint)));


     // prepare Simulator
    simulator = new QTimer(this);
    connect(simulator,SIGNAL(timeout()),SLOT(simulateData()));
    simdata = (float*)malloc(ADC_BLOCK_SIZE * sizeof(float));
    // program parameters
    m_parameters = new ParamModel(this);
    loadParameters();
}

// ******************** Programm Settings *****************************
ParamModel *Crusher::getParameters() const
{
    return m_parameters;
}

void Crusher::saveParameters()
{
        ParamSaver saver;
        saver.save(m_parameters,trUtf8("Каналы"));
        applyParameters();
}

void Crusher::loadParameters()
{
        ParamSaver saver;
        saver.load(m_parameters,trUtf8("Каналы"));
        applyParameters();
}

void Crusher::applyParameters()
{
    bool ok;
    float filtr;
    for (int i = 0; i < 16 ; i++) {
       QVariant prm = m_parameters->index(i,PARAM_ALPHA).data();
       filtr = prm.toFloat(&ok);
       if (ok) setFilterAlpha(filtr,i);
    }
}
// **********************************************************************

Crusher *Crusher::instance()
{
    if(classAddress==NULL)
    {
        classAddress = new Crusher();
       classAddress->init();
    }
    return classAddress;
}

Crusher::~Crusher()
{
    free(simdata);
}

int Crusher::init()
{
    lastError =  adc->init(ADCCallBack);
   // classAddress = this;
    if(!QDir("Records").exists())
    {
        if(!QDir().mkdir("Records")) lastError = ERR_NODIR;
    }
    if(!QDir("Excel").exists())
    {
        if(!QDir().mkdir("Excel")) lastError = ERR_NODIR;
    }
    if(lastError==0) m_simul = false;
    return lastError;
}

QString Crusher::getLastError() const
{
    switch(lastError)
    {
    case ERR_LOAD:
        return trUtf8("Ошибка загрузки драйвера.\nРабота будет продолжена в режиме имитации");
        break;
    case ERR_SETUP:
        return trUtf8("Ошибка настройки устройства.\nРабота будет продолжена в режиме имитации");
        break;
    case ERR_INIT:
        return trUtf8("Ошибка инициализации устройства.\nРабота будет продолжена в режиме имитации");
        break;
    case ERR_NODIR:
        return trUtf8("Не удалось создать каталог для записи.\nРабота будет продолжена в режиме имитации");
        break;
    default:
        return trUtf8("Неизвестная ошибка");
        break;
    }
}

void Crusher::setFileprefix(QString prefix)
{
     m_prefix = prefix;
}

QString Crusher::fileprefix()
{
     return m_prefix;
}

QString Crusher::filename()
{
    return m_filename;
}

QString Crusher::fullFilename()
{
    return "Records/" + m_filename;
}

void Crusher::setFilterAlpha(float alpha,int ch)
{
    filter->setAlpha(alpha,ch);
}

float Crusher::filterAlpha(int ch)
{
    return filter->alpha(ch);
}

void Crusher::rec()
{
    QString alfFile;
    if(m_rec) return;
    m_rec = true;
    m_filename = m_prefix;
    if (m_prefix!="") m_filename += "_";
    m_filename = m_filename + QDateTime::currentDateTime().toString("dd_MM_yyyy_HH_mm_ss");
    alfFile =  "./Records/" +  m_filename  + ".alf";
    char *file = new char[alfFile.length() + 1];
    strcpy(file, alfFile.toLocal8Bit());
    m_hFile = SaveALFHeader(file, 0);
    emit modeChanged(Rec);
}

void Crusher::stop()
{
    if(!m_run) return;

    if(m_simul) simulator->stop();
    else adc->stop();
    m_run = false;

    if(m_rec)
    {
    m_rec = false;
    CloseALF(m_hFile);
    emit modeChanged(Stop);
    }
    emit modeChanged(End);
}

void Crusher::run()
{
    if(m_run) return;
    if(m_simul)
    {
        simulator->start(300);
         emit modeChanged(Sim);
    }
    else
    {
        adc->start();
         emit modeChanged(Run);
    }
    m_run = true;

}

bool Crusher::isRun()
{
   return m_run;
}

bool Crusher::isRec()
{
    return m_rec;
}

bool Crusher::isSim()
{
    return m_simul;
}

bool Crusher::isError()
{
    return lastError!=0;
}


void Crusher::simulateData()
{
    Q_CHECK_PTR(simdata);
    for(int i=0;i<(ADC_BLOCK_SIZE/ADC_CHANNEL_COUNT);i++)
    {
        for(int j=0;j<ADC_CHANNEL_COUNT;j++){
            int ptr = i*ADC_CHANNEL_COUNT + j;
            Q_ASSERT(ptr < ADC_BLOCK_SIZE);
           // simdata[ptr]= (sim_val+j)%10;
            simdata[ptr]= sin(sim_val+(j*0.50))*5+5;
            if(j==0)
            {
                float noise = (float)(qrand()%1000);
                noise=500-noise;
                noise/=1000;
                simdata[ptr]+= noise;
            }
        }
        sim_val+=0.003 ;
    }
    emit dataRecived(simdata,ADC_BLOCK_SIZE);
}

void Crusher::filterComplete(float * data, unsigned int size)
{
    if(  m_rec &&  m_hFile != INVALID_HANDLE_VALUE )
    {
        SaveBlock(m_hFile, data, size * 4);
    }
    emit dataChanged(data,size);
}

void Crusher::emitDataChanged(float *data, unsigned int size)
{
    emit dataRecived(data,size);
}


int __stdcall ADCCallBack(void* pObj, void*& pData, int size, int mode)
{
    (void*)pObj;
    if( pData == 0 || size <= 0 || mode != ADC_DATA_MODE_CONVERT2FLOAT )
        return 0;
    float* pf = (float*)pData;
    Crusher::instance()->emitDataChanged(pf,size);
    return 1;
}
