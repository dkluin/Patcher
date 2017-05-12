#pragma once

#include "Main.h"
#include "Memory.h"
#include <initializer_list>

/*
	TODO:

	- Sort this into different files in Hooking directory?
	- Proper patching with restore option 
	- Statistics integration?
*/

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
	static uint32_t MakeJMP(Memory* mem, uint32_t dest);
	static uint32_t MakeJMP(Memory* mem, void* dest);
	static uint32_t MakeJMP(uint32_t mem, uint32_t dest, bool bProtect = true);
	static uint32_t MakeJMP(uint32_t mem, void* dest, bool bProtect = true);
	static uint32_t MakeJMP(HMODULE mem, uint32_t dest, bool bProtect = true);
	static uint32_t MakeJMP(HMODULE mem, void* dest, bool bProtect = true);

	// Makes a CALL to a relative address or function
	static uint32_t MakeCALL(Memory* mem, uint32_t dest);
	static uint32_t MakeCALL(Memory* mem, void* dest);
	static uint32_t MakeCALL(uint32_t mem, uint32_t dest, bool bProtect = true);
	static uint32_t MakeCALL(uint32_t mem, void* dest, bool bProtect = true);

	// JMP functions
	static uint32_t MakeJE(uint32_t mem, uint32_t dest, bool bProtect = true);
	static uint32_t MakeJE(uint32_t mem, void* dest, bool bProtect = true);
	static uint32_t MakeJE(Memory* mem, uint32_t dest);
	static uint32_t MakeJE(Memory* mem, void* dest);
	static uint32_t MakeJA(uint32_t mem, uint32_t dest, bool bProtect = true);
	static uint32_t MakeJA(uint32_t mem, void* dest, bool bProtect = true);
	static uint32_t MakeJA(Memory* mem, uint32_t dest);
	static uint32_t MakeJA(Memory* mem, void* dest);

	// Injects a function patch on multiple addresses 
	// Memory protection is applied to all addresses defined
	static void MakeMultipleCALLs(std::initializer_list<uint32_t> m_vAddresses, uint32_t m_pDest, bool bProtect = true);
	static void MakeMultipleCALLs(std::initializer_list<uint32_t> m_vAddresses, void* m_pDest, bool bProtect = true);
	static void MakeMultipleCALLs(std::initializer_list<Memory*> m_vAddresses, uint32_t m_pDest);
	static void MakeMultipleCALLs(std::initializer_list<Memory*> m_vAddresses, void* m_pDest);
	static void MakeMultipleJMPs(std::initializer_list<uint32_t> m_vAddresses, uint32_t m_pDest, bool bProtect = true);
	static void MakeMultipleJMPs(std::initializer_list<uint32_t> m_vAddresses, void* m_pDest, bool bProtect = true);
	static void MakeMultipleJMPs(std::initializer_list<Memory*> m_vAddresses, uint32_t m_pDest);
	static void MakeMultipleJMPs(std::initializer_list<Memory*> m_vAddresses, void* m_pDest);

	// Writes memory to multiple addresses
	template <class T>
	static void WriteMemoryMultipleAddresses(std::initializer_list<uint32_t> m_vAddresses, T m_Value, bool bProtect = true)
	{
		for (auto m_nAddress : m_vAddresses)
		{
			WriteMemory<T>(m_nAddress, m_Value, bProtect);
		}
	}

	template <class T>
	static void WriteMemoryMultipleAddresses(std::initializer_list<Memory*> m_vAddresses, T m_Value, bool bProtect = true)
	{
		for (auto m_nAddress : m_vAddresses)
		{
			WriteMemory<T>(m_nAddress->GetAddress(), m_Value, bProtect);
		}
	}

	// Read/Write - replacement for Memory.Get
	template <class T>
	static T ReadMemory(uint32_t address, bool bProtect = true)
	{
		Memory mem(address);
		mem.SetVirtualProtect(bProtect);
		return mem.Get<T>();
	}

	template <class T>
	static T ReadMemory(Memory* m_pAddress)
	{
		return m_pAddress->Get<T>(bProtect);
	}

	template <class T>
	static void WriteMemory(uint32_t address, T value, bool bProtect = true)
	{
		Memory mem(address);
		mem.SetVirtualProtect(bProtect);
		mem.Set<T>(value);
	}

	// Same variant, but with Memory class
	template <class T>
	static void WriteMemory(Memory* m_pAddress, T m_Value)
	{
		m_pAddress->Set<T>(m_Value);
	}

	// NOPs data
	static void MakeNOP(Memory* mem, uint32_t m_dwSize);
	static void MakeNOP(uint32_t mem, uint32_t m_dwSize, bool bProtect = true);

	// Makes a return (0xC3 RET)
	static void MakeRET(Memory* mem);
	static void MakeRET(uint32_t mem, bool bProtect = true);

	// Makes a return (0xC2 RET)
	static void MakeRET(Memory* mem, uint16_t pop);
	static void MakeRET(uint32_t mem, uint16_t pop, bool bProtect = true);

	// Makes a function return NULL
	static void MakeRET0(Memory* mem);
	static void MakeRET0(uint32_t mem, bool bProtect = true);

	// Gets a relative address
	static uint32_t GetRelativeAddress(uint32_t src, uint32_t dest);
	static uint32_t GetRelativeAddress(uint32_t src, void* dest);
};