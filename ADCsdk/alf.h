#ifndef ALF_H
#define ALF_H

#include "ADCsdk/IADCDevice.h"

HANDLE      SaveALFHeader(char* fpath, char format);
/*---------------------------------------------------------, ADCParametersBLOCK& pb-------------*/
void        CloseALF(HANDLE& hFile);
/*----------------------------------------------------------------------*/
int         SaveBlock(HANDLE hFile, void* ptr, int size);
#endif // ALF_H

