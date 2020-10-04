#pragma once
#include <iostream>
#include <Windows.h>
#include <Psapi.h>
#include <TlHelp32.h>
#include <vector>

namespace MemoryHelperCpp {
	class ProcessHelper {
	public:
		/// <summary>
		/// Process information
		/// </summary>
		PROCESS_INFORMATION pInfo;

		/// <summary>
		/// Create ProcessHelper instance
		/// </summary>
		ProcessHelper();

		/// <summary>
		/// Start new process and create ProcessHelper instance
		/// </summary>
		/// <param name="Path">Path to exe file</param>
		/// <returns>Operation result as boolean</returns>
		bool Start(LPSTR Path);

		/// <summary>
		/// Close stored process
		/// </summary>
		void Close();

		/// <summary>
		/// Get main module
		/// </summary>
		/// <returns>Module address</returns>
		DWORD MainModuleAddress();

		/// <summary>
		/// Get module by name
		/// </summary>
		/// <param name="Module">Module name</param>
		/// <returns>Module address</returns>
		DWORD ModuleAddress(const char* Module);

		/// <summary>
		/// Enumerata all modules
		/// </summary>
		/// <returns>Modules lisst</returns>
		std::vector<MODULEENTRY32> EnumModules();

		/// <summary>
		/// Find process by id
		/// </summary>
		/// <param name="PID">Process ID</param>
		/// <returns>ProcessHelper instance</returns>
		static ProcessHelper GetProcess(DWORD PID);

		/// <summary>
		/// Find process by name
		/// </summary>
		/// <param name="Name">Process executable name</param>
		/// <returns>ProcessHelper instance</returns>
		static ProcessHelper GetProcess(const char* Name);   
		
	};
}