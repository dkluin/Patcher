#pragma once

#include <cstdint>
#include <Windows.h>

namespace Memory
{
	/////////////// General functions - no specific stuff here
	class General
	{
	public:
		// memcpy with memory protection
		static void MemCpyWithMemoryProtect(void* dest, const void* src, size_t size)
		{
			memcpy(dest, src, size);
		}
		static void MemCpyWithMemoryProtect(uint32_t dest, const void* src, size_t size)
		{
			MemCpyWithMemoryProtect((void*)dest, src, size);
		}
	};

	/////////////// Global functions - global stuff
	class Global
	{
	public:
		// Initialize the memory patching library
		static bool InitializePatcher();

		// Shutdown the memory patching library
		static bool ShutdownPatcher();
	};
}