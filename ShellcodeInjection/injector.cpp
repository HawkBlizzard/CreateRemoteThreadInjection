// injector.cpp

#include "injector.h"


// ファイルのデータを読み取る
std::vector<BYTE> ReadFileBytes(const std::wstring& filePath) {

    // ファイルを開く
    HANDLE fileHandle = CreateFile(filePath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    // ファイルサイズを取得
    DWORD fileSize = GetFileSize(fileHandle, NULL);

    // バッファを確保
    std::vector<BYTE> fileBytes(fileSize);

    // ファイルを読み込む
    ReadFile(fileHandle, fileBytes.data(), fileSize, nullptr, nullptr);

    return fileBytes;
}


// プロセス名からプロセスIDを取得
DWORD GetProcessIdByProcessName(std::wstring& processName) {

	// プロセスのスナップショットを取得
	HANDLE snapProcessHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32W processEntry = { sizeof(PROCESSENTRY32W) };

	// 最初のプロセス情報を取得
	BOOL hasNextProcess = Process32First(snapProcessHandle, &processEntry);

	// スナップショットのファイル名とターゲットプロセス名を比較
	for (; hasNextProcess; hasNextProcess = Process32Next(snapProcessHandle, &processEntry)) {
		if (processName == processEntry.szExeFile) {
			return processEntry.th32ProcessID;
		}
	}

	return 0;
}
