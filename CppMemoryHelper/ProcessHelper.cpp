#include "ProcessHelper.h"

using namespace MemoryHelperCpp;

ProcessHelper::ProcessHelper() {
	ZeroMemory(&pInfo, sizeof(pInfo));
};

bool ProcessHelper::Start(LPSTR Path) {
	BOOL created;
	//store process information
	STARTUPINFO startInfo;
	PROCESS_INFORMATION procInfo;

	//set structs size
	ZeroMemory(&startInfo, sizeof(startInfo));
	startInfo.cb = sizeof(startInfo);

	//run process
	created = CreateProcess(
		NULL, //process path
		Path, //arguments
		NULL, //process inheritable
		NULL, //phread inheritable
		FALSE, //set inheritance
		0, //creating flags
		NULL, //enviroment
		NULL, //start directory
		&startInfo, //startupinfo pointer
		&pInfo //process info pointer
	);

	//return result
	return created;
}
void ProcessHelper::Close() {
	//close process
	TerminateProcess(pInfo.hProcess, 0);

	//close handles
	CloseHandle(pInfo.hThread);
	CloseHandle(pInfo.hProcess);
}
DWORD ProcessHelper::MainModuleAddress() {
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pInfo.dwProcessId);
	DWORD modAddress = 0;

	MODULEENTRY32 modEntry = { 0 };
	modEntry.dwSize = sizeof(MODULEENTRY32);

	if (Module32First(hSnap, &modEntry)) {
		modAddress = (DWORD)modEntry.modBaseAddr;
	}
	return modAddress;
}
DWORD ProcessHelper::ModuleAddress(const char* Module) {
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pInfo.dwProcessId);
	DWORD modAddress = 0;

	MODULEENTRY32 modEntry{ 0 };
	modEntry.dwSize = sizeof(MODULEENTRY32);

	if (Module32First(hSnap, &modEntry)) {
		do {
			if (strcmp(modEntry.szModule, Module) == 0) {
				modAddress = (DWORD)modEntry.modBaseAddr;
				break;
			}
		} while (Module32Next(hSnap, &modEntry));
	}
	return modAddress;
}
std::vector <MODULEENTRY32> ProcessHelper::EnumModules() {
	std::vector< MODULEENTRY32 > mArr;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pInfo.dwProcessId);
	DWORD modAddress = 0;

	MODULEENTRY32 modEntry{ 0 };
	modEntry.dwSize = sizeof(MODULEENTRY32);

	if (Module32First(hSnap, &modEntry)) {
		do {
			mArr.push_back(modEntry);
		} while (Module32Next(hSnap, &modEntry));
	}

	return mArr;
}
ProcessHelper ProcessHelper::GetProcess(DWORD PID) {
	HANDLE hPSnap;
	PROCESSENTRY32 pEntry;

	hPSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pEntry.dwSize = sizeof(PROCESSENTRY32);

	//create process helper
	ProcessHelper helper = ProcessHelper();

	//get first process
	if (Process32First(hPSnap, &pEntry)) {
		//if process id match
		if (pEntry.th32ProcessID == PID) {
			//set ids
			helper.pInfo.dwProcessId = pEntry.th32ProcessID;
			helper.pInfo.dwThreadId = pEntry.cntThreads;
			
			//set handlers
			helper.pInfo.hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, helper.pInfo.dwProcessId);
			helper.pInfo.hThread = OpenThread(THREAD_ALL_ACCESS, false, helper.pInfo.dwThreadId);
		}
		else {
			//go throug other processes
			while (Process32Next(hPSnap, &pEntry)) {
				//if process id match
				if (pEntry.th32ProcessID == PID) {

					//set ids
					helper.pInfo.dwProcessId = pEntry.th32ProcessID;
					helper.pInfo.dwThreadId = pEntry.cntThreads;

					//set handlers
					helper.pInfo.hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, helper.pInfo.dwProcessId);
					helper.pInfo.hThread = OpenThread(THREAD_ALL_ACCESS, false, helper.pInfo.dwThreadId);
					break;
				}
			}
		}
	}
	//return helper
	return helper;
}
ProcessHelper ProcessHelper::GetProcess(const char* Name) {
	HANDLE hPSnap;
	PROCESSENTRY32 pEntry;

	hPSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pEntry.dwSize = sizeof(PROCESSENTRY32);

	//create process helper
	ProcessHelper helper = ProcessHelper();

	//get first process
	if (Process32First(hPSnap, &pEntry)) {

		//if process name match
		if (strcmp(pEntry.szExeFile, Name) == 0) {
			//set ids
			helper.pInfo.dwProcessId = pEntry.th32ProcessID;
			helper.pInfo.dwThreadId = pEntry.cntThreads;

			//set handlers
			helper.pInfo.hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, helper.pInfo.dwProcessId);
			helper.pInfo.hThread = OpenThread(THREAD_ALL_ACCESS, false, helper.pInfo.dwThreadId);
		}
		else {
			//go throug other processes
			while (Process32Next(hPSnap, &pEntry)) {

				//if process name match
				if (strcmp(pEntry.szExeFile, Name) == 0) {
					//set ids
					helper.pInfo.dwProcessId = pEntry.th32ProcessID;
					helper.pInfo.dwThreadId = pEntry.cntThreads;

					//set handlers
					helper.pInfo.hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, helper.pInfo.dwProcessId);
					helper.pInfo.hThread = OpenThread(THREAD_ALL_ACCESS, false, helper.pInfo.dwThreadId);
					break;
				}
			}
		}
	}
	//return helper
	return helper;
}