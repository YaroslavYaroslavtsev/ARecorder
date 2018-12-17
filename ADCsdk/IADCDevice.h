#ifndef __ADC_DEVICE_H__
#define __ADC_DEVICE_H__

#include "ADC_CONST.h"
#include "windows.h"

//////////////////////////////////////////////////////////////////////////
//  Revision :  07-05-2008
//////////////////////////////////////////////////////////////////////////

#pragma pack(1)
/*######################################################################*/
/*  LOWORD is major version, HIWORD is minor version                    */
/*                          minor|major                                 */ 
#define MAJOR_VERSION       0xF010      // essential change
#define MINOR_VERSION       0x0002      // not essential change
#define CURRENT_VERSION     (MAJOR_VERSION | (MINOR_VERSION << 16))
/*######################################################################*/
#ifndef DIM
#define DIM(a)      (sizeof(a) / sizeof(a[0]))
#endif

#ifndef INTERRUPT_MESSAGE_STRUCTURE
#define INTERRUPT_MESSAGE_STRUCTURE
struct  Interrupt_Message
{
    unsigned        m_hWnd;             // HWND
    unsigned        m_uMessage;         // UINT
    unsigned        m_uLParam;          // LPARAM
};
#endif
/*----------------------------------------------------------------------*/
struct  ADCParametersBase
{
    int             m_nType;
    int             m_nSizeOf;
};
/*----------------------------------------------------------------------*/
struct  IADCDevice
{
    virtual unsigned __stdcall  AddRef() = 0;
    virtual unsigned __stdcall  Release() = 0;

    virtual int      __stdcall  Setup(int baseAdr, int DRQ, int IRQ, HANDLE hEvent) = 0;
    virtual int      __stdcall  Test() = 0;
    virtual int      __stdcall  Init(int mode, ADCParametersBase*, float*) = 0;
    virtual int      __stdcall  Start() = 0;
    virtual void     __stdcall  Stop() = 0;
    virtual int      __stdcall  GetData(int mode, void* pAdr, int size, int offset) = 0;
    virtual int      __stdcall  PortIO(int mode, void* pAdr, int size) = 0;
    virtual int      __stdcall  Get(int mode, void* value) = 0;
    virtual void     __stdcall  ClearInterrupt() = 0;
};
/*######################################################################*/
//  m_nType = ADC_DMA_TYPE
struct  ADCParametersDMA : public ADCParametersBase
{
    int             m_nStartOf;
    int             m_nIntOf;
    int             m_nDMABlockSize;
    int             m_nDMAMode;
    float           m_fFreqStart;
    int             m_nTimerStart;
    float           m_fFreqPack;
    int             m_nTimerPack;
    int             m_nFirstChannel;
    int             m_nChannelNumber;
    int             m_nGain;

    ADCParametersDMA()
    {
        m_nType   = ADC_DMA_TYPE;
        m_nSizeOf = sizeof(ADCParametersDMA);
    }
};
/*######################################################################*/
//  m_nType = ADC_DMAEX_TYPE
struct  ADCParametersDMAEX : public ADCParametersBase
{
    int*            m_pnGains;
    int*            m_pnChannels;
    int             m_nSize;
    int             m_nControl;
    int             m_nSyncLevel[2];

    ADCParametersDMAEX()
    {
        m_nType   = ADC_DMAEX_TYPE;
        m_nSizeOf = sizeof(ADCParametersDMAEX);
    }
};
/*######################################################################*/
//  m_nType = ADC_CALIBRATION_TYPE
struct  ADCParametersCALIBRATION : public ADCParametersBase
{
    unsigned        m_nFlags;
    int             m_nADC;             // sise of ADC table
    int*            m_pnADCGain;
    double*         m_pADCOffset;
    double*         m_pADCGain;
    int             m_nDAC;             // sise of DAC table
    double*         m_pDACOffset;
    double*         m_pDACGain;
    unsigned        m_nExtra;

    ADCParametersCALIBRATION()
    {
        m_nType   = ADC_CALIBRATION_TYPE;
        m_nSizeOf = sizeof(ADCParametersCALIBRATION);
        m_nFlags  = 0;
    }
};
/*######################################################################*/
//  m_nType = ADC_GENERATOR_TYPE
struct  ADCParametersGENERATOR : public ADCParametersBase
{
    int             m_nMode;
    double          m_fFreq;
    int             m_nAddress;
    union
    {
    int             m_nAmplitude;       // index
    float           m_fAmplitude;       // amplitude in Volts
    };
    int             m_nSize;            // size of DAC table
    short*          m_pData;            // pointer to table

    ADCParametersGENERATOR()
    {
        m_nType   = ADC_GENERATOR_TYPE;
        m_nSizeOf = sizeof(ADCParametersGENERATOR);
    }
};
/*######################################################################*/
//  m_nType = ADC_DG_GENERATOR_TYPE
struct  ADCParametersDGGENERATOR : public ADCParametersBase
{
    double          m_fFreq;
    int             m_nMode;
    int             m_nChannel;
    int             m_nSize1;           // PCA1 Length
    int             m_nSize2;           // PCA2 Length

    ADCParametersDGGENERATOR()
    {
        m_nType   = ADC_DG_GENERATOR_TYPE;
        m_nSizeOf = sizeof(ADCParametersDGGENERATOR);
    }
};
/*######################################################################*/
//  m_nType = ADC_SAMPLE_TYPE
struct  ADCParametersSAMPLE : public ADCParametersBase
{
    int             m_nControl;
    int             m_nGain;
    int             m_nChannel;
    int             m_nValue;

    ADCParametersSAMPLE()
    {
        m_nType   = ADC_SAMPLE_TYPE;
        m_nSizeOf = sizeof(ADCParametersSAMPLE);
    }
};
/*######################################################################*/
//  m_nType = ADC_BLOCK_TYPE
struct  ADCParametersBLOCK : public ADCParametersBase
{
    int             m_nStartOf;
    int             m_nBlockSize;
    int             m_nMode;
    int             m_nControl;
    int             m_nLevel;
    double          m_fFreqStart;
    double          m_fFreqPack;
    int             m_nChannelCount;
    int*            m_pnGains;
    int*            m_pnChannels;

    ADCParametersBLOCK()
    {
        m_nType   = ADC_BLOCK_TYPE;
        m_nSizeOf = sizeof(ADCParametersBLOCK);
    }
};
/*######################################################################*/
typedef int (__stdcall * ADCParametersSTREAMCallBack)(void*  pObj, 
                                                      void*& pData, int size, int mode);
/*----------------------------------------------------------------------*/
//  m_nType = ADC_STREAM_TYPE
struct  ADCParametersSTREAM : public ADCParametersBase
{
    ADCParametersSTREAMCallBack m_pCallBack; 
    void*                       m_vCallBackObj;
    void*                       m_vCallBackData;
    int                         m_vCallBackSize;
    int                         m_vCallBackMode;

    ADCParametersBLOCK          m_Block;

    ADCParametersSTREAM()
    {
        m_nType   = ADC_STREAM_TYPE;
        m_nSizeOf = sizeof(ADCParametersSTREAM);
    }
};
/*######################################################################*/
#define     ADC_ARRAY           64
/*----------------------------------------------------------------------*/
struct  ChannellParam
{
    int             m_nNumber;
    int             m_nGain;
    unsigned char   m_nView;
    unsigned char   m_nMode;
    unsigned char   m_nADC;
    unsigned char   m_nReserved1;
    COLORREF        m_RGB;
    short           m_nIGain;
    short           m_nIGain2;

    ChannellParam()
    {
        m_nNumber    = 0;
        m_nGain      = 0;
        m_nView      = 0;
        m_nMode      = 0;
        m_nADC       = 0;
        m_nReserved1 = 0;
        m_RGB        = RGB(0, 0, 0);
        m_nIGain     = 0;
        m_nIGain2    = 0;
    }
};

struct  ChannellProp
{
    int             m_nSize;
    int             m_nProperty[8];
    double          m_dFreq1;
    double          m_dFreq2;
    ChannellParam   m_Param[ADC_ARRAY];

    ChannellProp() : m_nSize(0), m_dFreq1(0.0), m_dFreq2(0.0) 
    {
        for(int i = 0; i < DIM(m_nProperty); ++i)
            m_nProperty[i] = 0;
    }
};
/*======================================================================*/
//  m_nType = ADC_CHANNELL_DIALOG_TYPE
struct  ADCParametersDialog : public ADCParametersBase
{
    ChannellProp        m_CProp;
    int                 m_nGains[ADC_ARRAY];
    int                 m_nChannels[ADC_ARRAY];
    ADCParametersBLOCK  m_Block;

    ADCParametersDialog()
    {
        m_nType   = ADC_DIALOG_TYPE;
        m_nSizeOf = sizeof(ADCParametersDialog);
    }
};
/*----------------------------------------------------------------------*/
//  m_nType = ADC_COLORVIEW_DIALOG_TYPE
struct  ADCParametersColorViewDialog : public ADCParametersBase
{
    int             m_nSize;
    COLORREF        m_RGBView[ADC_ARRAY];

    ADCParametersColorViewDialog()
    {
        m_nType   = ADC_COLORVIEW_DIALOG_TYPE;
        m_nSizeOf = sizeof(ADCParametersColorViewDialog);
    }
};
/*######################################################################*/
#define     IALF_UNDEFINE               0
#define     IALF_BLOCKSIZE              1
#define     IALF_CHANNELLS              2
#define     IALF_FREQ_FLOAT             3
#define     IALF_FREQ_DOUBLE            4
#define     IALF_CYCLEMODE              5
#define     IALF_SIZE_IN_SAMPLES        6
#define     IALF_SIZE_IN_SECTORS        7
#define     IALF_SYSTEMTIME             8
#define     IALF_FILETIME               9
/*======================================================================*/
struct  IALF
{
    virtual unsigned __stdcall  AddRef() = 0;
    virtual unsigned __stdcall  Release() = 0;

    virtual int      __stdcall  Open(TCHAR* path) = 0;
    virtual int      __stdcall  Reset(unsigned sector = 0, char flag = 0) = 0;
    virtual int      __stdcall  GetIndex(int mode, void* obuff) = 0;
    virtual unsigned __stdcall  GetVoltage(int mode, void* po, unsigned size) = 0;
    virtual int      __stdcall  Get(int mode, void* value) = 0;
};
/*######################################################################*/
#pragma pack()
#endif
