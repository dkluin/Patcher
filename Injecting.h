#pragma once

#include "Main.h"
#include "Memory.h"
#include <initializer_list>

/*
	TODO:

	- Sort this into different files in Hooking directory?
	- Proper patching with restore option 
*/

class MemoryInjector
{
public:
	// Makes a JMP to a relative address or function
	static void MakeJMP(Memory* mem, uint32_t dest);
	static void MakeJMP(Memory* mem, void* dest);

	static inline void MakeJMP(uint32_t mem, uint32_t dest, bool bProtect = true)
	{
		WriteMemory<uint8_t>(mem, 0xE9, bProtect);
		WriteMemory<uint32_t>(mem + 1, GetRelativeAddress(mem + 1, dest - 4), bProtect);
	}

	static inline void MakeJMP(uint32_t mem, void* dest, bool bProtect = true)
	{
		WriteMemory<uint8_t>(mem, 0xE9, bProtect);
		WriteMemory<uint32_t>(mem + 1, GetRelativeAddress(mem + 1, reinterpret_cast<uint32_t>(dest) - 4), bProtect);
	}

	template <typename Address, typename Destination>
	static inline void MakeJmpEx(Address mem, Destination dest, bool bProtect = true)
	{
		WriteMemory<uint8_t>(mem, 0xE9, bProtect);

		uint32_t dwHook;
		_asm
		{
			mov		eax, dest
			mov		dwHook, eax
		}

		WriteMemory<ptrdiff_t>(mem + 1, GetRelativeAddress((uint32_t)mem + 1, (uint32_t)dwHook - 4), bProtect);
	}

	// Makes a CALL to a relative address or function
	static void MakeCALL(Memory* mem, uint32_t dest);
	static void MakeCALL(Memory* mem, void* dest);

	template <typename Address, typename Destination>
	static inline void MakeCallEx(Address mem, Destination dest, bool bProtect = true)
	{
		WriteMemory<uint8_t>(mem, 0xE8, bProtect);

		uint32_t dwHook;
		_asm
		{
			mov		eax, dest
			mov		dwHook, eax
		}

		WriteMemory<ptrdiff_t>(mem + 1, GetRelativeAddress((uint32_t)mem + 1, (uint32_t)dwHook - 4), bProtect);
	}

	static inline void MakeCALL(uint32_t mem, uint32_t dest, bool bProtect = true)
	{
		WriteMemory<uint8_t>(mem, 0xE8, bProtect);
		WriteMemory<uint32_t>(mem + 1, GetRelativeAddress(mem + 1, dest - 4), bProtect);
	}

	static inline void MakeCALL(uint32_t mem, void* dest, bool bProtect = true)
	{
		WriteMemory<uint8_t>(mem, 0xE8, bProtect);
		WriteMemory<uint32_t>(mem + 1, GetRelativeAddress(mem + 1, reinterpret_cast<uint32_t>(dest) - 4), bProtect);
	}

	// Makes a JE
	static inline void MakeJE(uint32_t mem, uint32_t dest, bool bProtect = true)
	{
		WriteMemory<uint16_t>(mem, 0x840F, bProtect);
		WriteMemory<uint32_t>(mem + 2, GetRelativeAddress(mem, dest - 6), bProtect);
	}

	static inline void MakeJE(uint32_t mem, void* dest, bool bProtect = true)
	{
		WriteMemory<uint16_t>(mem, 0x840F, bProtect);
		WriteMemory<uint32_t>(mem + 2, GetRelativeAddress(mem, reinterpret_cast<uint32_t>(dest) - 6), bProtect);
	}

	static void MakeJE(Memory* mem, uint32_t dest);
	static void MakeJE(Memory* mem, void* dest);

	// Makes a JA 
	static inline void MakeJA(uint32_t mem, uint32_t dest, bool bProtect = true)
	{
		WriteMemory<uint16_t>(mem, 0x870F, bProtect);
		WriteMemory<uint32_t>(mem + 2, GetRelativeAddress(mem, dest - 6), bProtect);
	}

	static inline void MakeJA(uint32_t mem, void* dest, bool bProtect = true)
	{
		WriteMemory<uint16_t>(mem, 0x870F, bProtect);
		WriteMemory<uint32_t>(mem + 2, GetRelativeAddress(mem, reinterpret_cast<uint32_t>(dest) - 6), bProtect);
	}

	static void MakeJA(Memory* mem, uint32_t dest);
	static void MakeJA(Memory* mem, void* dest);

	// Injects a function patch on multiple addresses 
	// Memory protection is applied to all addresses defined, unless when using Memory classes
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
	inline static void WriteMemoryMultipleAddresses(std::initializer_list<uint32_t> m_vAddresses, T m_Value, bool bProtect = true)
	{
		for (auto m_nAddress : m_vAddresses)
		{
			WriteMemory<T>(m_nAddress, m_Value, bProtect);
		}
	}

	template <class T>
	inline static void WriteMemoryMultipleAddresses(std::initializer_list<Memory*> m_vAddresses, T m_Value, bool bProtect = true)
	{
		for (auto m_nAddress : m_vAddresses)
		{
			WriteMemory<T>(m_nAddress->GetAddress(), m_Value, bProtect);
		}
	}

	// Read/Write - replacement for Memory.Get
	template <class T>
	inline static T ReadMemory(uint32_t address, bool bProtect = true)
	{
		DWORD m_OldVirtualProtect[2];

		if (bProtect)
		{
			VirtualProtect(reinterpret_cast<void*>(address), sizeof(T), PAGE_EXECUTE_READWRITE, &m_OldVirtualProtect[0]);
			return *reinterpret_cast<T*>(address);
			VirtualProtect(reinterpret_cast<void*>(address), sizeof(T), m_OldVirtualProtect[0], &m_OldVirtualProtect[1]);
		}
		else
		{
			return *reinterpret_cast<T*>(address);
		}
	}

	template <class T>
	inline static T ReadMemory(Memory* m_pAddress)
	{
		return m_pAddress->Get<T>();
	}

	template <class T>
	inline static void WriteMemory(uint32_t address, T value, bool bProtect = true)
	{
		DWORD m_OldVirtualProtect[2];

		if (bProtect)
		{
			VirtualProtect(reinterpret_cast<void*>(address), sizeof(T), PAGE_EXECUTE_READWRITE, &m_OldVirtualProtect[0]);
			*reinterpret_cast<T*>(address) = value;
			VirtualProtect(reinterpret_cast<void*>(address), sizeof(T), m_OldVirtualProtect[0], &m_OldVirtualProtect[1]);
		}
		else
		{
			*reinterpret_cast<T*>(address) = value;
		}
	}

	// Same variant, but with Memory class
	template <class T>
	inline static void WriteMemory(Memory* m_pAddress, T m_Value)
	{
		m_pAddress->Set<T>(m_Value);
	}

	// NOPs data
	static void MakeNOP(Memory* mem, uint32_t m_dwSize);
	static void MakeNOP(uint32_t mem, uint32_t m_dwSize, bool bProtect = true);

	// Ranged NOPs
	static void MakeRangedNOP(Memory* m_pMemoryStart, Memory* m_pMemoryEnd);
	static void MakeRangedNOP(uint32_t m_MemoryStart, uint32_t m_MemoryEnd);
	static void MakeRangedNOP(Memory* m_pMemoryStart, uint32_t m_MemoryEnd);
	static void MakeRangedNOP(uint32_t m_MemoryStart, Memory* m_pMemoryEnd);

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