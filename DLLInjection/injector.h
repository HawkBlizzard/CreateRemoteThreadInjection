// injector.h

#pragma once

#include <Windows.h>
#include <TlHelp32.h>

#include <iostream>


// �֐��錾
DWORD GetProcessIdByProcessName(std::wstring& processName);