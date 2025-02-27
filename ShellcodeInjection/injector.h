// injector.h

#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <vector>



// ŠÖ”’è‹`
std::vector<BYTE> ReadFileBytes(const std::wstring& filePath);
DWORD GetProcessIdByProcessName(std::wstring& processName);