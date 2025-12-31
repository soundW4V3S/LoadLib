#pragma once
#include <Windows.h>   // WinAPI

void p(const wchar_t* t);
void welcome();
bool isDLL(std::wstring);
bool verifyDLLPath(std::wstring path);
bool verifyProcessName(std::wstring name);
DWORD getProcID(std::wstring procName);