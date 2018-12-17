/*######################################################################*/
//  Copyright(C) 2003-2004 ADCLab.      www.adclab.ru
//  Written by Andry Zharov.            adc@ru.ru, adc@adclab.ru
//  08.03.2004
/*######################################################################*/
#ifndef __DllClient_h__
#define __DllClient_h__

#include    <windows.h>
#include    <winreg.h>
#include    <tchar.h>
#include    "ifactory.h"

#include    "REGKEY\VTE_Drivers.ri"
#include    "REGKEY\VTE_Library.ri"
/*######################################################################*/
#define     TstrADD(d, s) if(s && *s) _tcscat(_tcscat(d, "\\"), s)
/*######################################################################*/
class   DllClient
{
private:
    void*   m_pStaticResident;
    HMODULE m_hLib;

public:
    DllClient()
    {
        m_hLib = 0;
        m_pStaticResident = 0;
    }
/*======================================================================*/
void*   LoadByPath(TCHAR const* szPath, char const* szExportName)
{
    Free();

    if(szPath == 0 || szExportName == 0) 
        return 0;
    m_hLib = HMODULE(::LoadLibrary(szPath));
    if(m_hLib == 0) 
        return 0;
    return m_pStaticResident = (void*)::GetProcAddress(m_hLib, szExportName);
}
/*----------------------------------------------------------------------*/
void*   LoadRegistered(TCHAR const* szCompanyName,
                       TCHAR const* szProductName,
                       TCHAR const* szVersionName,
                       TCHAR const* szModuleName,
                       char  const* szExportName = "StaticFactory")
{
    Free();

    TCHAR szPath[256];

    if(szCompanyName == 0 || szProductName == 0 || szVersionName == 0)
    {
        GetCurrentDirectory(sizeof(szPath), szPath);
        TstrADD(szPath, szModuleName);
        _tcscat(szPath, _T(".DLL"));
        return LoadByPath(szPath, szExportName);
    }

    _tcscpy(szPath, _T("SOFTWARE"));
    TstrADD(szPath, szCompanyName);
    TstrADD(szPath, szProductName);
    TstrADD(szPath, szVersionName);
    TstrADD(szPath, szModuleName);
    HKEY hKeyModule;
    LONG r = RegOpenKeyEx(HKEY_LOCAL_MACHINE, szPath, 0, KEY_READ, &hKeyModule);
    if(r != ERROR_SUCCESS)
        return 0;
    unsigned long dwType, dwSize = sizeof(szPath)/sizeof(TCHAR);
    r = RegQueryValueEx(hKeyModule, _T("path"), 0, &dwType,
                          (unsigned char*)szPath, &dwSize);
    RegCloseKey(hKeyModule);
    if(r != ERROR_SUCCESS || dwType != REG_SZ) 
        return 0;
    return LoadByPath(szPath, szExportName);
}
/*----------------------------------------------------------------------*/
void    Free()
{
    if(m_hLib) 
    { 
        FreeLibrary(m_hLib);
        m_hLib = 0; 
    }
    m_pStaticResident = 0;
}
/*----------------------------------------------------------------------*/
static
TCHAR*  GetRegName(TCHAR* data, int size, int index,
                   TCHAR const* szCompanyName,
                   TCHAR const* szProductName,
                   TCHAR const* szVersionName)
{
    if(data == 0 || size < 2 || index < 0) 
        return 0;

    TCHAR szPath[256];

    _tcscpy(szPath, _T("SOFTWARE"));
    TstrADD(szPath, szCompanyName);
    TstrADD(szPath, szProductName);
    TstrADD(szPath, szVersionName);
    HKEY hKeyModule;
    LONG r = RegOpenKeyEx(HKEY_LOCAL_MACHINE, szPath, 0, KEY_READ, &hKeyModule);
    if(r != ERROR_SUCCESS)
        return 0;
    DWORD dwSize = (size-1)*sizeof(TCHAR);
    FILETIME filetime;
    r = RegEnumKeyEx(hKeyModule, index, data, &dwSize, 0, 0, 0, &filetime);
    data[dwSize] = 0;
    ::RegCloseKey(hKeyModule);
    if(r != ERROR_SUCCESS) 
        return 0;
    return data;
}
/*----------------------------------------------------------------------*/
static
TCHAR*  GetInterfaceName(char* data, int size,
                         TCHAR const* szCompanyName,
                         TCHAR const* szProductName,
                         TCHAR const* szVersionName,
                         TCHAR const* szModuleName)
{
    if(data == 0 || size < 2)
        return 0;

    TCHAR szPath[256];

    _tcscpy(szPath, _T("SOFTWARE"));
    TstrADD(szPath, szCompanyName);
    TstrADD(szPath, szProductName);
    TstrADD(szPath, szVersionName);
    TstrADD(szPath, szModuleName);
    HKEY hKeyModule;
    LONG r = RegOpenKeyEx(HKEY_LOCAL_MACHINE, szPath, 0, KEY_READ, &hKeyModule);
    if(r != ERROR_SUCCESS)
        return 0;
    unsigned long dwType;
    DWORD dwSize = (size-1)*sizeof(TCHAR);
    r = RegQueryValueEx(hKeyModule, _T("UIName"), 0, &dwType,
                        (unsigned char*)data, &dwSize);
    ::RegCloseKey(hKeyModule);
    if(r != ERROR_SUCCESS || dwType != REG_SZ) 
        return 0;
    return data;
}
/*----------------------------------------------------------------------*/
void*   LoadDriver(TCHAR* szModuleName,
                   TCHAR* szInterfaceName = 0,
                   void*  lpParam = 0)
{
    IFactory* pFactory;
    if(szInterfaceName == 0)
        szInterfaceName = _T("IADCDevice");
    pFactory = (IFactory*)LoadRegistered(CompanyNameDRV,
                                         ProductNameDRV,
                                         VersionNameDRV,
                                         szModuleName);
    return (pFactory) ? pFactory->Create(szInterfaceName, lpParam) : 0;
}
/*----------------------------------------------------------------------*/
void*   LoadLibrary(TCHAR* szModuleName,
                    TCHAR* szInterfaceName,
                    void*  lpParam = 0)
{
    IFactory* pFactory;
    pFactory = (IFactory*)LoadRegistered(CompanyNameLIB,
                                         ProductNameLIB,
                                         VersionNameLIB,
                                         szModuleName);
    return (pFactory) ? pFactory->Create(szInterfaceName, lpParam) : 0;
}
};
/*######################################################################*/
#endif
