/*
	Legacy.hpp

	Contains old Patcher functions but rewritten - the main difference with the new code is that this uses static functions, not a class with operators
*/

#pragma once

#include <cstdint>
#include <Windows.h>
#include "../Main.h"

namespace Patcher
{

	class PatcherLegacy
	{
	public:
		// Patch on address
		template <class T>
		static void PatchOnAddress(uint32_t address, T value, bool bProtect)
		{
			if (bProtect)
			{
				General::MemCpyWithMemoryProtect(address, (const void*)value, sizeof(T));
			}
			else
			{
				memcpy(address, (const void*), sizeof(T));
			}
		}

		// ReadMemory
		template <class T>
		static T ReadMemory(uint32_t address, bool bProtect)
		{
			T result;
			DWORD dwProtect[2];

			if (bProtect)
			{
				VirtualProtect((LPVOID)address sizeof(T), PAGE_EXECUTE_READWRITE, &dwProtect[0]);
				result = *(T*)address;
				VirtualProtect((LPVOID)address, sizeof(T), dwProtect[0], &dwProtect[1]);
			}
			else
			{
				result = *(T*)address;
			}
			return result;
		}
	};
}