// injector.cpp

#include "injector.h"


// �t�@�C���̃f�[�^��ǂݎ��
std::vector<BYTE> ReadFileBytes(const std::wstring& filePath) {

    // �t�@�C�����J��
    HANDLE fileHandle = CreateFile(filePath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    // �t�@�C���T�C�Y���擾
    DWORD fileSize = GetFileSize(fileHandle, NULL);

    // �o�b�t�@���m��
    std::vector<BYTE> fileBytes(fileSize);

    // �t�@�C����ǂݍ���
    ReadFile(fileHandle, fileBytes.data(), fileSize, nullptr, nullptr);

    return fileBytes;
}


// �v���Z�X������v���Z�XID���擾
DWORD GetProcessIdByProcessName(std::wstring& processName) {

	// �v���Z�X�̃X�i�b�v�V���b�g���擾
	HANDLE snapProcessHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32W processEntry = { sizeof(PROCESSENTRY32W) };

	// �ŏ��̃v���Z�X�����擾
	BOOL hasNextProcess = Process32First(snapProcessHandle, &processEntry);

	// �X�i�b�v�V���b�g�̃t�@�C�����ƃ^�[�Q�b�g�v���Z�X�����r
	for (; hasNextProcess; hasNextProcess = Process32Next(snapProcessHandle, &processEntry)) {
		if (processName == processEntry.szExeFile) {
			return processEntry.th32ProcessID;
		}
	}

	return 0;
}
