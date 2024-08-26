#include <Windows.h>
#include "logger.hpp"
// BOOL WINAPI DllMain(
//     HINSTANCE handle, // handle to DLL module
//     DWORD reason,     // reason for calling function
//     LPVOID reserved)  // reserved
// {
//     // Perform actions based on the reason for calling.
//     switch (reason)
//     {
//     case DLL_PROCESS_ATTACH:
//         break;
//     case DLL_THREAD_ATTACH:
//         break;
//     case DLL_THREAD_DETACH:
//         break;
//     case DLL_PROCESS_DETACH:
//         break;
//     }
//     return TRUE;
// }

int main() {
    SetConsoleOutputCP(CP_UTF8);


    Logger log("DMA");

    log.print("hello world %p", nullptr);
    log.print("hello world 你好");
}