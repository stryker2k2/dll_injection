#include "shared_lib.h"

int pipeCommand(char *strCmd)
{
    char buffer[1024];
    FILE *pipe = popen(strCmd, "r");

    if (!pipe)
    {
        printf("[!] Cannot open %s pipe\n", strCmd);
        return 1;
    }

    printf("\nOutput\n=======\n");

    int c = 0;
    while(fgets(buffer, sizeof(buffer), pipe) != NULL)
    {
        c++;
        printf("%d) %s\n",c, buffer);
    }

    pclose(pipe);

    return 0;
}

int reportSuccess()
{
    printf("[+] Success!\n");

    return 0;
}

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpvReserved)
{
    // Perform actions based on the reason for calling.
    switch( fdwReason ) 
    { 
        case DLL_PROCESS_ATTACH:
         // Initialize once for each new process.
         // Return FALSE to fail DLL load.
            MessageBoxA(NULL, "Hello!", "From DLL", 0);
            break;

        case DLL_THREAD_ATTACH:
         // Do thread-specific initialization.
            break;

        case DLL_THREAD_DETACH:
         // Do thread-specific cleanup.
            break;

        case DLL_PROCESS_DETACH:
        
            if (lpvReserved != NULL)
            {
                break; // do not do cleanup if process termination scenario
            }
            
         // Perform any necessary cleanup.
            break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}