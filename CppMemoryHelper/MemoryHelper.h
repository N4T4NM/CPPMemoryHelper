#pragma once
#include "ProcessHelper.h"

namespace MemoryHelperCpp {
	class MemoryHelper
	{
	public:
		/// <summary>
		/// ProcessHelper instance
		/// </summary>
		ProcessHelper proc;

		/// <summary>
		/// Create MemoryHelper instance
		/// </summary>
		/// <param name="helper">ProcessHelper instance</param>
		MemoryHelper(ProcessHelper helper);

		/// <summary>
		/// Get process base address
		/// </summary>
		/// <param name="StartingAddress">Starting address</param>
		/// <returns>Porcess base address</returns>
		DWORD GetBaseAddress(DWORD StartingAddress);

		/// <summary>
		/// Get value from process address
		/// </summary>
		/// <typeparam name="T">Type to be returned</typeparam>
		/// <param name="MemoryAddress">Address to read</param>
		/// <returns>Value converted to Type</returns>
		template <typename T>
		T ReadMemory(DWORD MemoryAddress) {
			T buffer;
			ReadProcessMemory(proc.pInfo.hProcess, (void*)MemoryAddress, &buffer, sizeof(T), NULL);
			return buffer;
		}

		/// <summary>
		/// Write value to process address
		/// </summary>
		/// <typeparam name="T">Type to be written</typeparam>
		/// <param name="MemoryAddress">Address to write</param>
		/// <param name="Value">Value to write</param>
		/// <returns>Operation result as boolean</returns>
		template <typename T>
		bool WriteMemory(DWORD MemoryAddress, T Value) {
			T buffer = Value;
			return WriteProcessMemory(proc.pInfo.hProcess, (void*)MemoryAddress, &buffer, sizeof(buffer), NULL);
		}

		/// <summary>
		/// Calculate pointer
		/// </summary>
		/// <param name="BaseAddress">Process base address</param>
		/// <param name="Offsets">Pointer offsets</param>
		/// <returns>Calculated pointer</returns>
		DWORD CalculatePointer(DWORD BaseAddress, int Offsets[]);
	};
}