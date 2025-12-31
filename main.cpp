#include <iostream>
#include <string>  // For string

#include "handlers.h"


int main()
{
    welcome();

    while (1)  // Lifetime loop
    {
        std::wstring DLLpath;    // 2 vars to be entered by user. Using std::wstring for Unicode
        std::wstring procName;   

        std::wcout << "Please enter the path of the DLL you'd like to inject (No need for quotation marks):\n\n> ";
        std::getline(std::wcin, DLLpath);


        // Check Path validity
        while (1)
        {
            if (verifyDLLPath(DLLpath))  // If-valid path
            {
                if (isDLL(DLLpath))  // If-valid DLL
                {
                    std::wcout << "\n\nFound DLL! Please type the target process name:\n\n> ";  // Continue below for injection process
                    break;  // Break from loop
                }
                else if (isDLL(DLLpath) == NULL)
                {
                    std::wcout << "\n\nPath is not a DLL! Please enter a valid DLL as path (Relative to your drive (C, D ..)):\n\n> ";
                    std::getline(std::wcin, DLLpath);
                }
            }
            else if (verifyDLLPath(DLLpath) == NULL)  // If-invalid
            {
                std::wcout << "\n\nInvalid path! Please retype a valid path.\n\n> ";
                std::getline(std::wcin, DLLpath);
            }
        }

        // Input process name
        std::getline(std::wcin, procName);

        // Check Process Name validity
        while (1)
        {
            if (verifyProcessName(procName))  // If-valid
            {
                std::wcout << "\n\nFound process! Injecting selected DLL ... Waiting 5 seconds before reinitialization ...\n\n\n";
                break;
            }
            else if (verifyProcessName(procName) == NULL)  // If-invalid
            {
                std::wcout << "\n\nInvalid name! Please retype a valid active process name.\n\n> ";
                std::getline(std::wcin, procName);
            }
        }


        DWORD procID = 0;

        while (!procID)    // While procID is not found (base is set to 0, we need to find and set it to break loop)
        {
            procID = getProcID(procName);
            Sleep(30);  // Less CPU intensive
        }

        HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, procID);

        if (hProc && (hProc != INVALID_HANDLE_VALUE))
        {
            size_t bytes = (DLLpath.size() + 1) * sizeof(wchar_t);

            // Allocate memory in an external process, and we know which process via hProc Handle
            void* loc = VirtualAllocEx(hProc, nullptr, bytes, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

            // If location is valid
            if (loc)
            {
                WriteProcessMemory(hProc, loc, DLLpath.c_str(), bytes, nullptr);
            }

            // Load library (with LoadLibraryA) with "loc" DLL path as parameter
            HANDLE hThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryW, loc, 0, 0);


            if (hThread)
            {
                WaitForSingleObject(hThread, INFINITE);
                CloseHandle(hThread);
            }
        }

        if (hProc)
        {
            CloseHandle(hProc);
        }

        Sleep(5000);  // Sleeping for 5 seconds (5000 milliseconds) before returning
    }
    return 0;
}