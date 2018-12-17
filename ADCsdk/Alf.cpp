#include    <Windows.h>
#include "alf.h"
#include "ADCsdk/IADCDevice.h"
/*######################################################################*/
#ifndef DIM
#define DIM(a)      (sizeof(a) / sizeof(a[0]))
#endif
/*######################################################################*/
#pragma pack(1)
/*======================================================================*/
struct  ALFHEADERS
{
private:
    char            m_sRecordName[24];

    void    Fill(char* name)
    {
        for(int i = 0; i < sizeof(m_sRecordName); ++i)
            m_sRecordName[i] = (name && *name) ? *name++ : ' ';
        m_nRecordSize = 0L;
    }

public:
    __int64         m_nRecordSize;

    ALFHEADERS(char* name)
    {
        Fill(name);
    }

    ALFHEADERS()
    {
        Fill("ADCLABFFS");
    }
};
/*----------------------------------------------------------------------*/
struct  SAMPLESFMT : ALFHEADERS
{
    enum MaskFlags
    {
        SFMT_CHANNELS_COUNT             = 0x01,
        SFMT_FREQUENCY                  = 0x02,
        SFMT_TYPE                       = 0x04,
        SFMT_MODE                       = 0x08,
    };

    enum SamplesType
    {
        SAMPLES_TYPE_FLOAT              = 1,
        SAMPLES_TYPE_DOUBLE             = 2,
        SAMPLES_TYPE_SIGNED_INT8        = 3,
        SAMPLES_TYPE_UNSIGNED_INT8      = 4,
        SAMPLES_TYPE_SIGNED_INT16       = 5,
        SAMPLES_TYPE_UNSIGNED_INT16     = 6,
        SAMPLES_TYPE_SIGNED_INT32       = 7,
        SAMPLES_TYPE_UNSIGNED_INT32     = 8,
    };

    unsigned        m_mask;
    int             m_channelsCount;
    double          m_frequencyPerChannel;
    char            m_samplesType;
    char            m_lowerSignificantBit;
    char            m_significantBitsCount;
    char            m_mode;

    void    Fill(double freq, int chan, char format)
    {
        m_channelsCount       = chan;
        m_frequencyPerChannel = freq;
        m_samplesType         = format ? SAMPLES_TYPE_DOUBLE : SAMPLES_TYPE_FLOAT;
    }

    SAMPLESFMT() : ALFHEADERS("SAMPLES_FORMAT") 
    {
        m_nRecordSize = sizeof(SAMPLESFMT) - sizeof(ALFHEADERS);

        m_mask                  = SFMT_CHANNELS_COUNT | SFMT_FREQUENCY | SFMT_TYPE;
        m_channelsCount         = 0;
        m_frequencyPerChannel   = 0.0;
        m_samplesType           = SAMPLES_TYPE_FLOAT;
        m_lowerSignificantBit   = 0;
        m_significantBitsCount  = 0;
        m_mode                  = 1;
    }
};
/*----------------------------------------------------------------------*/
struct  SAMPLES_RECORD : ALFHEADERS
{
    SAMPLES_RECORD() : ALFHEADERS("SAMPLES_RECORD")
    {
        m_nRecordSize = -1L;
    }
};
/*======================================================================*/
struct  ALFFileHeader
{
//  Заголовок, как минимум, состоит из следующих структур:
//  ALFHEADER, SAMPLESFMT, SAMPLES_RECORD

    ALFHEADERS      alfh; 
    SAMPLESFMT      sfmt; 
    SAMPLES_RECORD  srec;

    void    Save(HANDLE hFile)
    {
        if(hFile == INVALID_HANDLE_VALUE)
            return;
        static DWORD dw = 0;
        WriteFile(hFile, this, sizeof(*this), &dw, 0);
    }
};
/*======================================================================*/
#pragma pack()
/*################################################, ADCParametersBLOCK& pb######################*/
HANDLE      SaveALFHeader(char* fpath, char format)
{
    unsigned nChan = 16; //pb.m_nChannelCount;
    //if(pb.m_nControl & ADC_BLOCK_CONTROL_GAIN_PAIR)
    //    nChan *= 2;
    if(nChan == 0)
        return 0;
    double freq = 2000; //pb.m_fFreqStart / pb.m_nChannelCount;

    HANDLE hFile = CreateFile(fpath, GENERIC_WRITE, 0, 0,
                              CREATE_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, 0);
    if(hFile == INVALID_HANDLE_VALUE)
        return hFile;

    ALFFileHeader alf;

    alf.sfmt.Fill(freq, nChan, format);

    alf.Save(hFile);

    return hFile;
}
/*----------------------------------------------------------------------*/
void        CloseALF(HANDLE& hFile)
{
    if(hFile != INVALID_HANDLE_VALUE)
    {
        CloseHandle(hFile);
        hFile = INVALID_HANDLE_VALUE;
    }
}
/*----------------------------------------------------------------------*/
int         SaveBlock(HANDLE hFile, void* ptr, int size)
{
    if(hFile == INVALID_HANDLE_VALUE)
        return 0;
    static DWORD dw = 0;
    return WriteFile(hFile, ptr, size, &dw, 0);
}
/*######################################################################*/
