#pragma once

#include <cstdint>
#include <Windows.h>

/////////////// General functions - no specific stuff here
class General
{
public:
	// memcpy with memory protection
	static void MemCpyWithMemoryProtect(void* dest, const void* src, size_t size)
	{
		DWORD dwProtect[2];
		VirtualProtect(dest, size, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
		memcpy(dest, src, size);
		VirtualProtect(dest, size, dwProtect[0], &dwProtect[1]);
	}
	static void MemCpyWithMemoryProtect(uint32_t dest, const void* src, size_t size)
	{
		MemCpyWithMemoryProtect((void*)dest, src, size);
	}

	// Protect
};