#pragma once

#include "Main.hpp"

namespace Memory
{
	class MemoryInjector
	{
	public:
		// Makes a JMP to a relative address or function
		static void MakeJMP(Memory* mem, uint32_t dest, bool bProtect);
		static void MakeJMP(Memory* mem, void* dest, bool bProtect);
		static void MakeJMP(uint32_t mem, uint32_t dest, bool bProtect);
		static void MakeJMP(uint32_t mem, void* dest, bool bProtect);

		// Makes a CALL to a relative address or function
		static void MakeCALL(Memory* mem, uint32_t dest, bool bProtect);
		static void MakeCALL(Memory* mem, void* dest, bool bProtect);
		static void MakeCALL(uint32_t mem, uint32_t dest, bool bProtect);
		static void MakeCALL(uint32_t mem, void* dest, bool bProtect);

	private:
		// Gets a relative address
		static Memory* GetRelativeAddress(Memory* src, Memory* dest);
		static uint32_t GetRelativeAddress(uint32_t src, uint32_t dest);
	};
}