/*
	Main.hpp

	Contains the main memory patching stuff
*/

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

	/////////////// New code which uses operators for comparing, setting, and even adding, multiplying, and much more 
	class Memory
	{
	private:
		uint32_t Address;

	public:
		Memory();
		Memory(uint32_t addr) { Address = addr; }

		// Alternative for getting a value of an address but memory protection is a problem
		template <class T>
		inline void Get(T& value)
		{
			DWORD dwProtect[2];
			VirtualProtect(this->Address, sizeof(T), PAGE_EXECUTE_READWRITE, &dwProtect[0]);
			*(T*)this->Address = value;
			VirtualProtect(this->Address, sizeof(T), dwProtect[0], &dwProtect[1]);
		}

		// Operators
		template <class T>
		inline void operator=(const T& value) { *(T*)this->Address = value; }

		template <class T>
		inline void operator+(const T& value) { *(T*)this->Address = *(T*)this->Address + value; }

		template <class T>
		inline void operator-(const T& value) { *(T*)this->Address = *(T*)this->Address - value; }

		template <class T>
		inline void operator*(const T& value) { *(T*)this->Address = *(T*)this->Address * value; }

		template <class T>
		inline void operator/(const T& value) { *(T*)this->Address = *(T*)this->Address / value; }
		inline void operator%(const int& value) { *(int*)this->Address = *(int*)this->Address % value; }
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