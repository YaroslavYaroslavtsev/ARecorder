#ifndef __ADC_CONST_H__
#define __ADC_CONST_H__
/*######################################################################*/
// m_nStartOf values                            
#define     ADCPARAM_START_PROGRAMM             1
#define     ADCPARAM_START_TIMER                2
#define     ADCPARAM_START_EXT                  4
#define     ADCPARAM_START_COMP                 8    
                                                
// m_nIntOf values                              
#define     ADCPARAM_INT_NOTUSED                0
#define     ADCPARAM_INT_READY                  1
/*----------------------------------------------------------------------*/
// Get <mode> code                              
#define     ADC_GET_READY                       0
#define     ADC_GET_DATA                        1
#define     ADC_GET_DMACOUNTER                  2
#define     ADC_GET_DMACOUNTER0                 2
#define     ADC_GET_DMACOUNTER1                 3
#define     ADC_GET_INTERRUPT_READY             4
#define     ADC_GET_INTERRUPT_TC                5
#define     ADC_GET_INTERRUPT_EXT               6
#define     ADC_GET_ADCMODE                     7
#define     ADC_GET_STATUS                      8
#define     ADC_GET_COMP                        9
                                                
#define     ADC_GET_BASE                        10
#define     ADC_GET_IRQ                         11
#define     ADC_GET_DRQ                         12
#define     ADC_GET_DRQ0                        12
#define     ADC_GET_DRQ1                        13
#define     ADC_GET_CLOCK                       14
#define     ADC_GET_NAME                        15
#define     ADC_CALIBRATE                       16
                                                
#define     ADC_GET_CAPABILITY                  17 
#define     ADC_GET_CAPABILITY_EX               21
                                                
#define     ADC_GET_BASELIST                    18
#define     ADC_GET_IRQLIST                     19
#define     ADC_GET_DRQLIST                     20
#define     ADC_GET_DEFAULTBASEINDEX            22
#define     ADC_GET_DEFAULTIRQINDEX             23
#define     ADC_GET_DEFAULTDRQINDEX             24
                                                
#define     ADC_GET_MINFREQ                     25
#define     ADC_GET_MAXFREQ                     26
#define     ADC_GET_MINAMP                      27
#define     ADC_GET_MAXAMP                      28
                                                
#define     ADC_GET_FREQLIST                    29
                                                
#define     ADC_GET_DATASIZE                    30
#define     ADC_GET_DATABITS                    31
#define     ADC_GET_DATAMASK                    32
#define     ADC_GET_CHANNELMASK                 33
                                                
#define     ADC_GET_IRQMASK                     34
#define     ADC_GET_DRQMASK                     35
#define     ADC_GET_XC_STAT                     36
#define     ADC_GET_NCHANNEL                    37
                                                
#define     ADC_GET_SIZELIST                    38
#define     ADC_GET_SIZELIST_SIZE               39
#define     ADC_GET_FREQLIST_SIZE               40
                                                
#define     ADC_GET_BASELIST_SIZE               41
#define     ADC_GET_IRQLIST_SIZE                42
#define     ADC_GET_DRQLIST_SIZE                43
                                                
#define     ADC_GET_GAINLIST                    44
#define     ADC_GET_GAINLIST_SIZE               45
                                                
#define     ADC_GET_DATA_LSHIFT                 46
#define     ADC_GET_DATA_RSHIFT                 47
                                                
#define     ADC_GET_MEMORYSIZE                  48
#define     ADC_GET_PREHISTORY_SIZE             49
                                                
#define     ADC_ZERO_CALIBRATE                  50
#define     ADC_GET_DATA_EXT                    51
#define     ADC_GET_DRQ_MODE                    52
                                                
#define     ADC_GET_RANGE_BIPOLAR               53
#define     ADC_GET_RANGE_UNIPOLAR              54
                                                
#define     ADC_GET_ADDRESS                     55
                                                
#define     ADC_GET_PREHISTORY_INDEX            56
                                                
#define     ADC_GET_PACKETLIST                  57
#define     ADC_GET_PACKETLIST_SIZE             58
#define     ADC_GET_SYNCHRO_OFFSET              59
#define     ADC_GET_EXTSYNC_GAINLIST            60
#define     ADC_GET_EXTSYNC_GAINLIST_SIZE       61
                                                
#define     ADC_GET_GAINLIST_FLOAT              62
#define     ADC_GET_GAINLIST_FLOAT_SIZE         63
#define     ADC_GET_EXTSYNC_GAINLIST_FLOAT      64
#define     ADC_GET_EXTSYNC_GAINLIST_FLOAT_SIZE 65
#define     ADC_GET_PACKET_SIZE                 66

#define     ADC_GET_NEAREST_SYNTH_FREQ          67

#define     ADC_GET_IRQ_CLOCK                   68
#define     ADC_GET_TIME                        69
#define     ADC_GET_CYCLEBUFFER_SIZE            70
#define     ADC_GET_FIFO_SIZE                   71

#define     ADC_GET_SERIALNUMBER_STRING         100
#define     ADC_GET_MAXFREQ_MULTICHANNEL        101
#define     ADC_GET_MAXFREQ_MULTIADC            102

#define     ADC_GET_SERIALNUMBER_LONG           200
#define     ADC_GET_TEMP_SENSOR                 210
#define     ADC_INDEX_USER_DATA                 220
#define     ADC_WRITE_USER_DATA                 221
#define     ADC_READ_USER_DATA                  222

#define     ADC_READ_CALIBRATION                225
#define     ADC_SAVE_CALIBRATION                226

#define     ADC_GET_IADCUTILITY_STRING          255

#define     ADC_READ_SAMPLE                     500

#define     ADC_GET_CYCLE_BUFFER                601
#define     ADC_FREE_CYCLE_BUFFER               602

// Get[Set] <mode> code
#define     ADC_SET_ADCMODE_END                 1000
#define     ADC_SET_ADCMODE_START               1001
#define     ADC_SET_DRQ_MODE_SINGLE             1002
#define     ADC_SET_DRQ_MODE_DEMAND             1003
#define     ADC_SET_ADCMODE_DIFF                1004
#define     ADC_CLEARANDENABLE_IRQ              1020
#define     ADC_SET_ACTIVE_CHANNELL             1021
#define     ADC_SET_MODE_SLAVE                  1022
#define     ADC_SET_CLOCK_MODE                  1023
                                                
#define     ADC_SET_TOGGLELOADXILINX            2001
#define     ADC_SET_TOGGLECOMPATMODE            2002
#define     ADC_SET_TOGGLELOADCUSTOM            2003
#define     ADC_SET_FORCERELOADXILINX           2004
#define     ADC_SET_POWER_ON                    2005
#define     ADC_SET_POWER_OFF                   2006
#define     ADC_SET_TOGGLERACRESET              2007
#define     ADC_SET_FORCERACRESET               2008
                                                
#define     ADC_SET_LOADXILINX                  2009
#define     ADC_SET_DONOTLOADXILINX             2010
#define     ADC_SET_LOADCUSTOM                  2011
#define     ADC_SET_LOADSTANDARD                2012
#define     ADC_SET_RACRESET_ON                 2013
#define     ADC_SET_RACRESET_OFF                2014
#define     ADC_SET_RELOADXILINX                2015
#define     ADC_SET_ADDRESS                     2016
#define     ADC_SET_RESET_RAC                   2017 
#define     ADC_GET_ISLABPCP                    2018
                                                
#define     ADC_SET_DMA_BUSMASTER_ENABLE        2020

#define     ADC_SET_USE_LONGPULSE_ONLY          2030
#define     ADC_SET_SYNCHRO_OFFSET_INDEX        2031

#define     ADC_SET_READUSERFLASH               2040
#define     ADC_SET_WRITEUSERFLASH              2041

// LOWORD is major version, HIWORD is minor version 
#define     ADC_GET_VERSION                     2000

// View codes
#define     ADC_GET_VIEW                        2100

// Static DAC code
#define     ADC_WRITE_DAC                       3000
                                                
// ADC_GET_CAPABILITY codes                     
#define     ADC_CAPS_DMA                        0x00000001
#define     ADC_CAPS_DMA0                       0x00000001
#define     ADC_CAPS_DMA1                       0x00000002
#define     ADC_CAPS_DMAHALF                    0x00000004
#define     ADC_CAPS_DMASWITCH                  0x00000008
                                                
#define     ADC_CAPS_INTERRUPT                  0x00000010
#define     ADC_CAPS_INTERRUPT0                 0x00000010
#define     ADC_CAPS_INTERRUPT1                 0x00000020
#define     ADC_CAPS_INTERRUPT_READY            0x00000040
#define     ADC_CAPS_INTERRUPT_TC               0x00000080
#define     ADC_CAPS_INTERRUPT_EXT              0x00000100
                                                
#define     ADC_CAPS_GENERATOR                  0x00000200
#define     ADC_CAPS_TIMER3                     0x00000400
#define     ADC_CAPS_TIMER8254                  0x00000400
#define     ADC_CAPS_EXTSTART                   0x00000800
                                                
#define     ADC_CAPS_MEMORY                     0x00001000
#define     ADC_CAPS_MEMORYPERCHANNEL           0x00002000
#define     ADC_CAPS_FREQLIST                   0x00004000
#define     ADC_CAPS_SIZELIST                   0x00008000
                                                
#define     ADC_CAPS_DIGITAL_IN                 0x00010000
#define     ADC_CAPS_DIGITAL_OUT                0x00020000
#define     ADC_CAPS_DIGITAL_16                 0x00040000
#define     ADC_CAPS_DIGITAL_32                 0x00080000
                                                
#define     ADC_CAPS_GAINSLIST                  0x00100000
#define     ADC_CAPS_PREHISTORY                 0x00200000
#define     ADC_CAPS_GAINSPERCHANNEL            0x00400000
                                                
#define     ADC_CAPS_FREQMODE2                  0x00800000
#define     ADC_CAPS_SYNCHROLEVEL               0x01000000
#define     ADC_CAPS_SYNCHROLOW                 0x02000000
#define     ADC_CAPS_SYNCHROHIGH                0x04000000
#define     ADC_CAPS_SYNCHRO2                   0x08000000
                                                
#define     ADC_CAPS_CHANNELDIR_GROWTH          0x10000000
#define     ADC_CAPS_CHANNELDIR_DECREASE        0x20000000
#define     ADC_CAPS_CHANNELDIR_FREE            0x40000000
                                                
#define     ADC_CAPS_CALIBRATE                  0x80000000
                                                
// ADC_GET_CAPABILITY_EX codes                  
#define     ADC_CAPS1_PCI                       0x00000000
#define     ADC_CAPS1_PCISLAVE                  0x00000001
#define     ADC_CAPS1_PCIMASTER                 0x00000002
#define     ADC_CAPS1_LPT                       0x00000010
#define     ADC_CAPS1_USB                       0x00000100
#define     ADC_CAPS1_USBBUFFER                 0x00000200

#define     ADC_CAPS2_MEMORY                    0x00000001
#define     ADC_CAPS2_MEMORY1                   0x00000002
#define     ADC_CAPS2_DMA                       0x00000004
#define     ADC_CAPS2_FIFO                      0x00000004
#define     ADC_CAPS2_DMAEX                     0x00000008
#define     ADC_CAPS2_SYNCHRO_CHANNELL          0x00000010
#define     ADC_CAPS2_CHANNELLIST               0x00000020
#define     ADC_CAPS2_DMA_COUNTER               0x00000100
#define     ADC_CAPS2_DMA_INTERRUPT             0x00000200

#define     ADC_CAPS2_SYNCHRO_BOARD             0x00100000
#define     ADC_CAPS2_SYNCHRO_BOARD_ALL         0x00200000
#define     ADC_CAPS2_SYNCHRO_BOARD_PAIR        0x00400000

#define     ADC_CAPS2_BLOCK                     0x01000000
#define     ADC_CAPS2_STREAM                    0x02000000
#define     ADC_CAPS2_GENERATOR                 0x04000000
#define     ADC_CAPS2_CALIBRATION               0x08000000

#define     ADC_CAPS3_ADCLAB                    0x80000000
                                                
// Init <mode> code                             
#define     ADC_INIT_MODE_CHECK                 0
#define     ADC_INIT_MODE_INIT                  1
#define     ADC_INIT_MODE_USER                  10
                                                
// Setup particular value IRQ                   
#define     ADC_SETUP_IRQ_MESSAGE               0x80000000
                                                
// GetData <mode> code                          
#define     ADC_DATA_MODE_DATAFROMDMA           0x00000000
#define     ADC_DATA_MODE_DATAFROMMEM           0x00000000
#define     ADC_DATA_MODE_DATAFROMDMA0          0x00000000
#define     ADC_DATA_MODE_DATAFROMDMA1          0x80000000
#define     ADC_DATA_MODE_DATAASIS              0x40000000
#define     ADC_DATA_MODE_DATACH0               0x20000000
#define     ADC_DATA_MODE_DATACH1               0x10000000
#define     ADC_DATA_MODE_DATABOTH              0x00000000
#define     ADC_DATA_MODE_DATASWAP              0x08000000
#define     ADC_DATA_MODE_DATAWRITE             0x04000000

#define     ADC_DATA_MODE_CONVERT2INT16         1
#define     ADC_DATA_MODE_CONVERT2INT16M        2
#define     ADC_DATA_MODE_CONVERT2INT32         3
#define     ADC_DATA_MODE_CONVERT2INT32M        4
#define     ADC_DATA_MODE_CONVERT2FLOAT         5
#define     ADC_DATA_MODE_CONVERT2DOUBLE        6
                                
// PortIO <mode> code
#define     ADC_PORTIO_DISABLE                   0
#define     ADC_PORTIO_OUTB                      1
#define     ADC_PORTIO_INB                      -1
#define     ADC_PORTIO_OUTW                      2
#define     ADC_PORTIO_INW                      -2
#define     ADC_PORTIO_OUTD                      3
#define     ADC_PORTIO_IND                      -3
                                                
// ERROR code                                   
#define     ADC_ERROR_NOTSUPPORTED               0
#define     ADC_ERROR_NOTINITIALIZE             -1
#define     ADC_ERROR_INVALIDPARAMETERS         -2
                                                
// ERROR Setup code                             
#define     ADC_ERROR_INVALIDBASE               -3
#define     ADC_ERROR_INVALIDIRQ                -4
#define     ADC_ERROR_INVALIDDRQ                -5
#define     ADC_ERROR_DRQ_ALLREADY_USED         -6
#define     ADC_ERROR_IRQ_ALLREADY_USED         -7
#define     ADC_ERROR_VXD_NOTLOADED             -10
#define     ADC_ERROR_VXD_INVALIDVERSION        -11
/*----------------------------------------------------------------------*/
#define     ADC_DMAEX_CONTROL_0_MASK            0x000000FF
#define     ADC_DMAEX_CONTROL_GAIN              0x00000001
#define     ADC_DMAEX_CONTROL_MODEDIFF          0x00000002
#define     ADC_DMAEX_CONTROL_GAIN_PAIR         0x00000010
#define     ADC_DMAEX_CONTROL_FLAG              0x80000000
/*----------------------------------------------------------------------*/
#define     ADC_GENERATOR_MODE_AUTO_START       0x80000000
#define     ADC_GENERATOR_MODE_CHANNEL_MASK     0x0000000F

#define     ADC_CHANNEL_MODEDIFF                0x80000000

#define     ADC_BLOCK_CONTROL_MODEZERO          0x00000001
#define     ADC_BLOCK_CONTROL_MODEDIFF          0x00000002
#define     ADC_BLOCK_CONTROL_ZERO_MUL          0x00000004
#define     ADC_BLOCK_CONTROL_GAIN_PAIR         0x00000010

#define     ADC_BLOCK_MODE_MODECYCLE            0x00000001
#define     ADC_BLOCK_MODE_MODECYCLE1           0x00000002
#define     ADC_BLOCK_MODE_MODECYCLE2           0x00000004
#define     ADC_BLOCK_MODE_MODECYCLE3           0x00000008
#define     ADC_BLOCK_MODE_MODECYCLE_EVENT      0x00000010
/*----------------------------------------------------------------------*/
#define     ADC_DMA_TYPE                        1
#define     ADC_DMAEX_TYPE                      4

#define     ADC_BLOCK_TYPE                      100
#define     ADC_STREAM_TYPE                     101
#define     ADC_GENERATOR_TYPE                  102
#define     ADC_SAMPLE_TYPE                     103
#define     ADC_DG_GENERATOR_TYPE               104

#define     ADC_DIALOG_TYPE                     190
#define     ADC_COLORVIEW_DIALOG_TYPE           191

#define     ADC_CALIBRATION_TYPE                300
/*######################################################################*/
#endif
