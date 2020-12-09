#ifndef __ARBITER_SERVICE_H
#define __ARBITER_SERVICE_H


#include <windows.h>

#include <winsvc.h>
#include <io.h>
#include "..\\inc\\F_IFACE.H"


#define NEW_DRIVER_PATH "c:\\windows\\system32\\drivers\\filehide_my.sys"

extern "C" __declspec(dllexport) void Arbiter_Service_Ins();
extern "C" __declspec(dllexport) void Arbiter_Service_unIns();

#endif