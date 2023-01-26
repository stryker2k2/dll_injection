#ifndef SHARED_LIB_H
#define SHARED_LIB_H

#include <stdio.h>
#include <windows.h>
#include <string.h>

#ifdef BUILD_MY_DLL
    #define SHARED_LIB __declspec(dllexport)
#else
    #define SHARED_LIB __declspec(dllimport)
#endif

int SHARED_LIB pipeCommand(char *strCmd);

int SHARED_LIB reportSuccess();

#endif // end of DLL