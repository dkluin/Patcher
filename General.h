#pragma once

#include <cstdint>
#include <Windows.h>

/////////////// General functions - no specific stuff here
class General
{
public:
	// memcpy with memory protection
	static void MemCpyWithMemoryProtect(uint32_t dest, uint32_t src, size_t size);

	// strncpy with memory protection
	static void StrNCpyWithMemoryProtect(void* dest, char* src, size_t size);
	static void StrNCpyWithMemoryProtect(uint32_t dest, char* src, size_t size);
};
