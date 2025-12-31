#pragma once
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <filesystem>


// INITIALIZERS - Functions used on program startup
// --
// Simple printing function for printing the main title
void p(std::wstring t)
{
	std::wcout << t << std::endl;
}

// Welcoming function basis to store and print title
void welcome()
{
	p(L" /$$                                 /$$ /$$       /$$ /$$      ");
	p(L"| $$                                | $$| $$      |__/| $$      ");
	p(L"| $$        /$$$$$$   /$$$$$$   /$$$$$$$| $$       /$$| $$$$$$$ ");
	p(L"| $$       /$$__  $$ |____  $$ /$$__  $$| $$      | $$| $$__  $$");
	p(L"| $$      | $$  \\ $$  /$$$$$$$| $$  | $$| $$      | $$| $$  \\ $$");
	p(L"| $$      | $$  | $$ /$$__  $$| $$  | $$| $$      | $$| $$  | $$");
	p(L"| $$$$$$$$|  $$$$$$/|  $$$$$$$|  $$$$$$$| $$$$$$$$| $$| $$$$$$$/");
	p(L"|________/ \\______/  \\_______/ \\_______/|________/|__/|_______/ \n\nThis program is intended for 32-bit process injection.\n\n");
}


// VERIFIERS - For checking that certain things exist
// --
// Verifier to see that we have a path to a valid file
bool verifyDLLPath(std::wstring path)  // Simply checks if the path is a valid path
{
	return std::filesystem::exists(path);
}

// Extension checker to ensure that we are targeting a DLL
bool isDLL(const std::wstring fileObject)
{
	std::filesystem::path p(fileObject);

	if (!p.has_extension())
	{
		return false;
	}

	std::wstring ext = p.extension().wstring();
	return _wcsicmp(ext.c_str(), L".dll") == 0;
}

// Verify if the process name exists within process Snapshot 
bool verifyProcessName(std::wstring name) 
{ 
	HANDLE hSnap; 
	PROCESSENTRY32W PE32; 
	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);  // Getting Snapshot 
	if (hSnap == INVALID_HANDLE_VALUE)  // Invalid handle error, return false so user can retype the process name 
	{ 
		std::wcout << "\n\nInvalid handle found! Please retype the program name.\n\n> "; 
		return false; 
	} 

	PE32.dwSize = sizeof(PROCESSENTRY32W); 

	if (Process32FirstW(hSnap, &PE32))  // If-valid Process32 entry 
	{ 
		do 
		{ 
			if (_wcsicmp(PE32.szExeFile, name.c_str()) == 0)  // If the process name is found, return back as true 
			{ 
				CloseHandle(hSnap);  // Free memory 
				return true; 
			} 
		} while (Process32NextW(hSnap, &PE32)); 
	} 
	CloseHandle(hSnap);  // No process name found, return false 
	return false; 
}


// Getting procID
DWORD getProcID(std::wstring procName) {
	DWORD procId = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnap != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32W PE32;
		PE32.dwSize = sizeof(PE32);

		if (Process32FirstW(hSnap, &PE32)) {
			do {

				if (_wcsicmp(PE32.szExeFile, procName.c_str()) == 0) {
					procId = PE32.th32ProcessID;
					break;
				}

			} while (Process32NextW(hSnap, &PE32));
		}
		CloseHandle(hSnap);
	}
	return procId;

}
