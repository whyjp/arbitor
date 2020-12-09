#ifndef __INSTALL_HFILE_DLL
#define __INSTALL_HFILE_DLL


#include "..\\inc\\4Svc_lib.h"


extern "C" __declspec(dllexport) void Arbiter_Driver_Ins(char* current_filepath,char* dest_filepath);
extern "C" __declspec(dllexport) void Arbiter_File_UnIns(char* del_filepath);

#endif