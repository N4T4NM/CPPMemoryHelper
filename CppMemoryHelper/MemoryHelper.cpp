#include "MemoryHelper.h"
using namespace MemoryHelperCpp;

MemoryHelper::MemoryHelper(ProcessHelper helper) {
	proc = helper;
};

DWORD MemoryHelper::GetBaseAddress(DWORD StartingAddress) {
	return proc.MainModuleAddress() + StartingAddress;
}

DWORD MemoryHelper::CalculatePointer(DWORD BaseAddress, int Offsets[]) {
	DWORD addr = BaseAddress;
	for (int i = 0; i < (sizeof(Offsets) / sizeof(Offsets[0]))-1; i++) {
		ReadProcessMemory(proc.pInfo.hProcess, (void*)addr, &addr, sizeof(DWORD), NULL) + Offsets[i];
	}
	return addr;
}