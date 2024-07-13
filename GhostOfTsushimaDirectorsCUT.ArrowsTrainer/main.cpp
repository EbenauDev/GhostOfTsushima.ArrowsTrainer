#include <cstdio>
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <future>


void* shortArrowsAddress = (void*)0x7FF689F8A058;
void* fireArrowsAddress = (void*)0x7FF689F8A05C;
void* heavyArrowsAddress = (void*)0x7FF689F8A060;


DWORD GetPidByName() {
	PROCESSENTRY32 singleProcess;
	HANDLE h = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	singleProcess.dwSize = sizeof(PROCESSENTRY32);

	do
	{
		if (_wcsicmp(singleProcess.szExeFile, L"GhostOfTsushima.exe") == 0) {
			DWORD pid = singleProcess.th32ProcessID;
			CloseHandle(h);
			return pid;
		}


	} while (Process32Next(h, &singleProcess));
	CloseHandle(h);
	return 0;

}

int reloadArrows(void* address, HANDLE processHandler) {
	int maxArrows = 20;
	int data = 0;
	int resultReader = ReadProcessMemory(processHandler, address, &data, sizeof(data), nullptr);
	if (resultReader == 0) {
		std::cout << "Cannot read process memory";
		return 0;
	}

	WriteProcessMemory(processHandler, address, &maxArrows, sizeof(maxArrows), nullptr);
	return 1;
}


int main() {
	DWORD pidNumber = GetPidByName();
	if (pidNumber == 0) {
		std::cout << "Not found GhostOfTsushima.exe in execution" << std::endl;
		return 0;
	}

	std::cout << "PID process GhostOfTsushima.exe is " << pidNumber << std::endl;

	HANDLE handleToProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, pidNumber);

	if (handleToProcess == NULL)
	{
		std::cout << "Failed open process GhostOfTsushima.exe" << std::endl;
		return 0;
	}

	while (true)
	{
		//CTRL-L + R
		if (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(0x52)) {
			std::async(&reloadArrows, shortArrowsAddress, handleToProcess);
			std::async(&reloadArrows, fireArrowsAddress, handleToProcess);
		}

		//CTRL-L + T
		if (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(0x54)) {
			std::async(&reloadArrows, heavyArrowsAddress, handleToProcess);
		}
	
	}
	return 1;
}