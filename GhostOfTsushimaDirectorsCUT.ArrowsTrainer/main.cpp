#include <cstdio>
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>


/*	Long bow address

	explosion arrows 0x2BA7BCF4390
	heavy arrows 0x7FF6885FA060
*/


/*	Short bow address

	short arrows 0x7FF6885FA058
	fire arrows 0x7FF6885FA05C


*/




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



int handlerShortArrowsBow(HANDLE processHandler) {
	const int MAX_ARROWS = 20;
	void *address = (void*)0x7ff6885fa058;

	int data = 0;

	int resultReader = ReadProcessMemory(processHandler, address, &data, sizeof(data), nullptr);
	if (resultReader == 0) {
		std::cout << "Cannot read process memory";
		return 0;
	}

	std::cout << "Current arrows: " << data << "\n";

	if (data == 0) {
		WriteProcessMemory(processHandler, address, &MAX_ARROWS, sizeof(MAX_ARROWS), nullptr);
	}
	else
	{
		int numberOfArrows = MAX_ARROWS - data;
		WriteProcessMemory(processHandler, address, &numberOfArrows, sizeof(numberOfArrows), nullptr);
	}
	return 1;
}

int handlerFireArrowsBow(HANDLE processHandler) {
	const int MAX_ARROWS = 20;
	void* address = (void*)0x7FF6885FA05C;

	int data = 0;

	int resultReader = ReadProcessMemory(processHandler, address, &data, sizeof(data), nullptr);
	if (resultReader == 0) {
		std::cout << "Cannot read process memory";
		return 0;
	}

	std::cout << "Current arrows: " << data << "\n";

	if (data == 0) {
		WriteProcessMemory(processHandler, address, &MAX_ARROWS, sizeof(MAX_ARROWS), nullptr);
	}
	else
	{
		int numberOfArrows = MAX_ARROWS - data;
		WriteProcessMemory(processHandler, address, &numberOfArrows, sizeof(numberOfArrows), nullptr);
	}
	return 1;
}


int handlerHeavyArrowsBow(HANDLE processHandler) {
	const int MAX_ARROWS = 20;
	void* address = (void*)0x7FF6885FA060;

	int data = 0;

	int resultReader = ReadProcessMemory(processHandler, address, &data, sizeof(data), nullptr);
	if (resultReader == 0) {
		std::cout << "Cannot read process memory";
		return 0;
	}

	std::cout << "Current arrows: " << data << "\n";

	if (data == 0) {
		WriteProcessMemory(processHandler, address, &MAX_ARROWS, sizeof(MAX_ARROWS), nullptr);
	}
	else
	{
		int numberOfArrows = MAX_ARROWS - data;
		WriteProcessMemory(processHandler, address, &numberOfArrows, sizeof(numberOfArrows), nullptr);
	}
	return 1;
}

int handlerExplosionArrowsBow(HANDLE processHandler) {
	const int MAX_ARROWS = 20;
	void* address = (void*)0x2BA7BCF4390;

	int data = 0;

	int resultReader = ReadProcessMemory(processHandler, address, &data, sizeof(data), nullptr);
	if (resultReader == 0) {
		std::cout << "Cannot read process memory";
		return 0;
	}

	std::cout << "Current arrows: " << data << "\n";

	if (data == 0) {
		WriteProcessMemory(processHandler, address, &MAX_ARROWS, sizeof(MAX_ARROWS), nullptr);
	}
	else
	{
		int numberOfArrows = MAX_ARROWS - data;
		WriteProcessMemory(processHandler, address, &numberOfArrows, sizeof(numberOfArrows), nullptr);
	}
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

	std::cout << "What do you want?\n\n";
	std::cout << "Type 1 to reload short arrows\n";
	std::cout << "Type 2 to reload fire arrows\n";
	std::cout << "Type 3 to reload heavy arrows\n";
	std::cout << "Type 4 to reload explosion arrows\n";

	int option = 0;
	std::cin >> option;

	switch (option) {
	case 1:
		handlerShortArrowsBow(handleToProcess);
	case 2:
		handlerFireArrowsBow(handleToProcess);
	case 3:
		handlerHeavyArrowsBow(handleToProcess);
	case 4:
		handlerExplosionArrowsBow(handleToProcess);
	default:
		break;
	}
	return 1;
}