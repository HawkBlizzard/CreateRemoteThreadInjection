// injector.h

#pragma once

#include <Windows.h>
#include <TlHelp32.h>

#include <iostream>


// ŠÖ”éŒ¾
DWORD GetProcessIdByProcessName(std::wstring& processName);