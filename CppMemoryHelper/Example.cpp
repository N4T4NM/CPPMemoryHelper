// CppMemoryHelper.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include "ProcessHelper.h"
#include "MemoryHelper.h"

using namespace MemoryHelperCpp;
int main()
{
    ProcessHelper prc;
    
    //create new process
    prc.Start((LPSTR)"PATH/TO/YOUR/PROCESS.exe");

    //get process by id
    prc = ProcessHelper::GetProcess((DWORD)0000);

    //get process by name
    prc = ProcessHelper::GetProcess("PROCES_NAME.exe");

    //enum modules
    prc.EnumModules();
    
    //get main module address
    prc.MainModuleAddress();
    //get module address by name
    prc.ModuleAddress("MODULE_NAME");

    //create MemoryHelper
    MemoryHelper helper = MemoryHelper(prc);
    
    //get base address
    DWORD base = helper.GetBaseAddress(0x000000);

    //get pointer
    int offsets[] = { 0x0, 0xA, 0xB };
    DWORD pointer = helper.CalculatePointer(base, offsets);

    //read memory value
    int intVal = helper.ReadMemory<int>(pointer);
    float floatVal = helper.ReadMemory<float>(pointer);

    //write memory value
    bool success = helper.WriteMemory<int>(pointer, 100);
    bool success = helper.WriteMemory<float>(pointer, 100.5);
}