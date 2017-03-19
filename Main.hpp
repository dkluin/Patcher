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
			DWORD pProtection[2];
			memcpy(dest, src, size);
		}
		static void MemCpyWithMemoryProtect(uint32_t dest, const void* src, size_t size)
		{
			MemCpyWithMemoryProtect((void*)dest, src, size);
		}
	};

	/////////////// New code which uses operators for comparing, setting, and even adding, multiplying, and much more 
	class Memory
	{
	private:
		uint32_t Address;

	public:
		Memory(uint32_t addr) { Address = addr; }

		// Operators
		template <class T>
		inline void operator=(const T& value)
		{
			*(uint32_t*)this->Address = value;
		}

		template <class T>
		inline void operator+(const T& value)
		{
			*(uint32_t*)this->Address = *(uint32_t*)this->Address + value;
		}

		template <class T>
		inline void operator-(const T& value)
		{
			*(uint32_t*)this->Address = *(uint32_t*)this->Address - value;
		}

		template <class T>
		inline void operator*(const T& value)
		{
			*(uint32_t*)this->Address = *(uint32_t*)this->Address * value;
		}

		template <class T>
		inline void operator/(const T& value)
		{
			*(uint32_t*)this->Address = *(uint32_t*)this->Address / value;
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