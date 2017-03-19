/*
	Legacy.hpp

	Contains old Patcher functions but rewritten - the main difference with the new code is that this uses static functions, not a class with operators
*/

#pragma once

#include <cstdint>
#include <Windows.h>
#include "../Main.hpp"

namespace Memory
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
	};
}