#pragma once

#include <cstdint>
#include <Windows.h>
#include <vector>
/////////////// New code which uses operators for comparing, setting, and even adding, multiplying, and much more 

enum eRestorableType
{
	RESTORE_NONE = 0,
	RESTORE_MEMORY_WRITE,
	RESTORE_JMP,
	RESTORE_CALL,
	RESTORE_RET_1,
	RESTORE_RET_2,
	RESTORE_RET_0,
	RESTORE_NOP,
	RESTORE_PLUGIN_JMP,
	RESTORE_PLUGIN_CALL,
	RESTORE_PLUGIN_RET
};

class Memory
{
protected:
	uint32_t Address;

	bool bShouldStoreOriginal : 1; // When setting memory, keep the original value.
	bool bRequiresVirtualProtection : 1; // We need to override the current address permissions when using the operators

	bool bOldVirtualProtect; // Old virtual protection setting 

	eRestorableType m_Type;

public:
	Memory() { Address = 0; };
	Memory(uint32_t addr) { Address = addr; }
	Memory(Memory* m_pMemory);

	// Change address
	void ChangeAddress(uint32_t newAddr) { Address = newAddr; }

	// Enable/disable virtual protection
	void SetVirtualProtect(bool m_bNewVirtualProtect)
	{
		bOldVirtualProtect = bRequiresVirtualProtection;
		bRequiresVirtualProtection = m_bNewVirtualProtect;
	}

	void RestoreVirtualProtect()
	{
		bRequiresVirtualProtection = bOldVirtualProtect;
	}

	bool GetVirtualProtect()
	{
		return bRequiresVirtualProtection;
	}

	// Enable/disable memory restore ability (kindof useless for Memory class)
	void ToggleRestorablePatching(bool m_bRestore)
	{
		bShouldStoreOriginal = m_bRestore;
	}

	// Sets memory value with protect parameter
	template <class T>
	inline void Set(T value)
	{
		DWORD dwProtect[2];

		if (bRequiresVirtualProtection)
		{
			VirtualProtect((void*)Address, sizeof(T), PAGE_EXECUTE_READWRITE, &dwProtect[0]);
			*(T*)Address = value;
			VirtualProtect((void*)Address, sizeof(T), dwProtect[0], &dwProtect[1]);
		}
		else
		{
			*(T*)Address = value;
		}
	}

	// Gets memory value with virtual protect parameter
	template <class T>
	inline T Get()
	{
		T result;
		DWORD dwProtect[2];

		if (bRequiresVirtualProtection)
		{
			VirtualProtect((LPVOID)Address, sizeof(T), PAGE_EXECUTE_READWRITE, &dwProtect[0]);
			result = *(T*)Address;
			VirtualProtect((LPVOID)Address, sizeof(T), dwProtect[0], &dwProtect[1]);
		}
		else
		{
			result = *(T*)Address;
		}
		return result;
	}

	// Returns the current address
	inline uint32_t GetAddress() { return Address; }

	// Comparison operators
	bool operator==(const Memory& m_Memory) const { return Address == m_Memory.Address; };
	bool operator>(const Memory& m_Memory) const { return Address > m_Memory.Address; };
	bool operator<(const Memory& m_Memory) const { return Address < m_Memory.Address; };
	bool operator>=(const Memory& m_Memory) const { return Address >= m_Memory.Address; };
	bool operator<=(const Memory& m_Memory) const { return Address <= m_Memory.Address; };
	bool operator!=(const Memory& m_Memory) const { return Address != m_Memory.Address; };

	// Normal operators
	Memory& operator+(const Memory& m_Memory) const { return Memory(Address + m_Memory.Address); };
	Memory& operator-(const Memory& m_Memory) const { return Memory(Address - m_Memory.Address); };
	Memory& operator*(const Memory& m_Memory) const { return Memory(Address * m_Memory.Address); };
	Memory& operator/(const Memory& m_Memory) const { return Memory(Address / m_Memory.Address); };
	Memory& operator%(const Memory& m_Memory) const { return Memory(Address % m_Memory.Address); };

	Memory& operator+=(const Memory& m_Memory) const { return Memory(Address + m_Memory.Address); };
	Memory& operator-=(const Memory& m_Memory) const { return Memory(Address - m_Memory.Address); };
	Memory& operator*=(const Memory& m_Memory) const { return Memory(Address * m_Memory.Address); };
	Memory& operator/=(const Memory& m_Memory) const { return Memory(Address / m_Memory.Address); };
	Memory& operator%=(const Memory& m_Memory) const { return Memory(Address % m_Memory.Address); };
};