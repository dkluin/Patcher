#pragma once

#include "Main.h"
#include "Memory.h"

enum eInjectorError
{
	INJECTOR_ERROR_NONE = 0,
	INJECTOR_ERROR_INVALID_MEMORY_PTR,
	INJECTOR_ERROR_UNKNOWN
};

class MemoryInjector
{
public:
	// Makes a JMP to a relative address or function
	static uint32_t MakeJMP(Memory* mem, uint32_t dest, bool bProtect = true);
	static uint32_t MakeJMP(Memory* mem, void* dest, bool bProtect = true);
	static uint32_t MakeJMP(uint32_t mem, uint32_t dest, bool bProtect = true);
	static uint32_t MakeJMP(uint32_t mem, void* dest, bool bProtect = true);
	static uint32_t MakeJMP(HMODULE mem, uint32_t dest, bool bProtect = true);
	static uint32_t MakeJMP(HMODULE mem, void* dest, bool bProtect = true);

	// Makes a CALL to a relative address or function
	static uint32_t MakeCALL(Memory* mem, uint32_t dest, bool bProtect = true);
	static uint32_t MakeCALL(Memory* mem, void* dest, bool bProtect = true);
	static uint32_t MakeCALL(uint32_t mem, uint32_t dest, bool bProtect = true);
	static uint32_t MakeCALL(uint32_t mem, void* dest, bool bProtect = true);
		
	// JMP functions
	static uint32_t MakeJE(uint32_t mem, uint32_t dest, bool bProtect);
	static uint32_t MakeJA(uint32_t mem, uint32_t dest, bool bProtect);

	// Read/Write - replacement for Memory.Get
	template <class T>
	static T ReadMemory(uint32_t address, bool bProtect = true)
	{
		Memory mem(address);
		return mem.Get<T>(bProtect);
	}

	template <class T>
	static void WriteMemory(uint32_t address, T value, bool bProtect = true)
	{
		Memory mem(address);
		mem.Set<T>(value, bProtect);
	}

	// NOPs data
	static void MakeNOP(Memory* mem, uint32_t m_dwSize, bool bProtect = true);
	static void MakeNOP(uint32_t mem, uint32_t m_dwSize, bool bProtect = true);

	// Makes a return (0xC3 RET)
	static void MakeRET(Memory* mem, bool bProtect = true);
	static void MakeRET(uint32_t mem, bool bProtect = true);

	// Makes a return (0xC2 RET)
	static void MakeRET(Memory* mem, uint16_t pop, bool bProtect = true);
	static void MakeRET(uint32_t mem, uint16_t pop, bool bProtect = true);

	// Makes a function return NULL
	static void MakeRET0(Memory* mem, bool bProtect = true);
	static void MakeRET0(uint32_t mem, bool bProtect = true);

private:
	// Gets a relative address
	static uint32_t GetRelativeAddress(uint32_t src, uint32_t dest);
};