#include "General.h"

namespace Patcher
{
	// memcpy with memory protection
	void General::MemCpyWithMemoryProtect(void* dest, const void* src, size_t size)
	{
		DWORD dwProtect[2];
		VirtualProtect(dest, size, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
		memcpy(dest, src, size);
		VirtualProtect(dest, size, dwProtect[0], &dwProtect[1]);
	}

	void General::MemCpyWithMemoryProtect(uint32_t dest, const void* src, size_t size)
	{
		MemCpyWithMemoryProtect((void*)dest, src, size);
	}

	// strncpy with memory protection
	void General::StrNCpyWithMemoryProtect(void* dest, char* src, size_t size)
	{
		DWORD dwProtect[2];
		VirtualProtect(dest, size, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
		strncpy((char*)dest, src, size);
		VirtualProtect(dest, size, dwProtect[0], &dwProtect[1]);
	}

	void General::StrNCpyWithMemoryProtect(uint32_t dest, char* src, size_t size)
	{
		DWORD dwProtect[2];
		VirtualProtect((void*)dest, size, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
		strncpy((char*)dest, src, size);
		VirtualProtect((void*)dest, size, dwProtect[0], &dwProtect[1]);
	}
}