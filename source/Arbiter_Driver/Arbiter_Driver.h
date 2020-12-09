#ifndef __ARBITER_DRIVER_H
#define __ARBITER_DRIVER_H


#include <windows.h>


#define SRVNAME "filehide_my"
#define NEW_DRIVER_PATH "c:\\windows\\system32\\drivers\\filehide_my.sys"

extern "C" __declspec(dllexport) void Arbiter_Driver_Ins();
extern "C" __declspec(dllexport) void Arbiter_Driver_unIns();

#endif