#include <stdio.h>
#include <windows.h>
#include "mmLoader.h"

// Loads a local DLL via LoadLibrary
FARPROC libLoad(char *dllName, char *procName)
{
    HINSTANCE hSharedLib =  LoadLibrary(dllName);

    if (!hSharedLib)
        { printf("[!] Failed to LoadLibrary\n"); exit(-1); }

    FARPROC lf_sharedLibCommand = (FARPROC)GetProcAddress(hSharedLib, procName);

    if (!lf_sharedLibCommand)
        { printf("[!] Failed to GetProcAddress\n"); exit(-1); }

    printf("[+] Successfully loaded %s from %s\n", procName, dllName);

    return lf_sharedLibCommand;
}

// Loads a local DLL into Memory then calls LoadLibary on the DLL in memory
FARPROC libLoadMemory(char *dllName, char *procName)
{
    FILE *fp = fopen(dllName, "r");

    if (!fp) 
        { printf("[!] Failed to load library\n"); exit(-1); }

    fseek(fp, 0, SEEK_END);
    long int fpSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    printf("[+] %s is %ld bytes\n", dllName, fpSize);

    char *dllBuffer = (char*)malloc(fpSize);

    fread((char *)dllBuffer, fpSize, 1, fp);

    // Prints "MZ" if all goes well
    printf("Magic Number: ");
    for(int i = 0x00; i <= 0x01; i++)
    {
        printf("%c", dllBuffer[i]);
    }

    fclose(fp);

    DWORD pdwError;

    HMEMMODULE hSharedLib = LoadMemModule(dllBuffer, FALSE, &pdwError);

    FARPROC fpSharedProc = GetMemModuleProc(hSharedLib, procName);

    free(dllBuffer);

    return fpSharedProc;
}

// Demonstrates different ways to load DLLs
int main(void)
{
    FARPROC lf_pipeCommand;
    FARPROC lf_reportSuccess;

    char cmd[16];
    printf("\nEnter a command: ");
    scanf("%s", cmd);

    // Load and run local DLL from disk
    // lf_pipeCommand = libLoad("shared_lib.dll", "pipeCommand");
    // lf_pipeCommand(cmd);
    // lf_reportSuccess = libLoad("shared_lib.dll", "reportSuccess");
    // lf_reportSuccess();

    // Copy local DLL from disk to memory then run DLL from memory
    lf_pipeCommand = libLoadMemory("shared_lib.dll", "pipeCommand");
    lf_pipeCommand(cmd);

    return EXIT_SUCCESS;
}