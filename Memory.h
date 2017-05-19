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

struct RestoreMemWrite
{
	size_t m_Size;
	uint8_t* m_Data;
};

struct RestoreMakeJMP
{
	uint32_t m_dwOldData[5];
};

struct RestoreMakeCALL
{
	uint32_t m_dwOldData[5];
};

struct RestoreMakeNOP
{
	size_t m_Size;
	uint8_t* m_Data;
};

class Memory
{
	friend class MemoryInjector;

protected:
	uint32_t Address;

	bool bShouldStoreOriginal : 1; // When setting memory, keep the original value. This however does not mean that you can re-apply a patch, for that use bRestoreablePatchingWithReApply
	bool bRequiresVirtualProtection : 1; // We need to override the current address permissions when using the operators
	bool bRestoreablePatchingWithReApply : 1; // Not only allows you to restore patches, but you may also re-apply them. 

	bool bOldVirtualProtect; // Old virtual protection setting 

public:
	// Restorable stuff		
	std::vector<RestoreMemWrite> m_RestoreMemWrite;
	std::vector<RestoreMakeJMP> m_RestoreMakeJMP;
	std::vector<RestoreMakeCALL> m_RestoreMakeCALL;
	std::vector<RestoreMakeNOP> m_RestoreMakeNOP;

protected:
	eRestorableType m_Type; // Used to tell which member of our union is active
	bool bOverrideRestorablePatching = false;
	bool bOverrideRestorablePatchingWithReApply = false;

public:
	Memory() { Address = 0; };
	Memory(uint32_t addr) { Address = addr; }
	Memory(Memory* m_pMemory);

	// Change address
	inline void ChangeAddress(uint32_t newAddr) { Address = newAddr; }

	// Enable/disable virtual protection
	inline void SetVirtualProtect(bool m_bNewVirtualProtect)
	{
		bOldVirtualProtect = bRequiresVirtualProtection;
		bRequiresVirtualProtection = m_bNewVirtualProtect;
	}

	inline void RestoreVirtualProtect()
	{
		bRequiresVirtualProtection = bOldVirtualProtect;
	}

	inline bool GetVirtualProtect()
	{
		return bRequiresVirtualProtection;
	}

	// Enable/disable memory restore ability (kindof useless for Memory class)
	inline void ToggleRestorablePatching(bool m_bRestore)
	{
		bShouldStoreOriginal = m_bRestore;
	}

	// Is restorable patching enabled?
	inline bool IsRestorablePatchingEnabled()
	{
		return bShouldStoreOriginal && !bOverrideRestorablePatching;
	}

	// Restore the active restoreable instance with our 

	// Sets memory value with protect parameter
	template <class T>
	inline void Set(T value)
	{
		DWORD m_OldVirtualProtect[2];

		if (bRequiresVirtualProtection)
		{
			VirtualProtect(reinterpret_cast<void*>(Address), sizeof(T), PAGE_EXECUTE_READWRITE, &m_OldVirtualProtect[0]);
			*reinterpret_cast<T*>(Address) = value;
			VirtualProtect(reinterpret_cast<void*>(Address), sizeof(T), m_OldVirtualProtect[0], &m_OldVirtualProtect[1]);
		}
		else
		{
			*reinterpret_cast<T*>(Address) = value;
		}
	}

	// Again, sets it with an offset...
	template <class T>
	inline void SetWithOffset(T value, uint32_t m_Offset)
	{
		DWORD m_OldVirtualProtect[2];

		if (bRequiresVirtualProtection)
		{
			VirtualProtect(reinterpret_cast<void*>(Address + m_Offset), sizeof(T), PAGE_EXECUTE_READWRITE, &m_OldVirtualProtect[0]);
			*reinterpret_cast<T*>(Address + m_Offset) = value;
			VirtualProtect(reinterpret_cast<void*>(Address + m_Offset), sizeof(T), m_OldVirtualProtect[0], &m_OldVirtualProtect[1]);
		}
		else
		{
			*reinterpret_cast<T*>(Address + m_Offset) = value;
		}
	}

	// Gets memory value with virtual protect parameter
	template <class T>
	inline T Get()
	{
		T result;
		DWORD m_OldVirtualProtect[2];

		if (bRequiresVirtualProtection)
		{
			VirtualProtect(reinterpret_cast<void*>(Address), sizeof(T), PAGE_EXECUTE_READWRITE, &m_OldVirtualProtect[0]);
			result = *reinterpret_cast<T*>(Address);
			VirtualProtect(reinterpret_cast<T*>(Address), sizeof(T), m_OldVirtualProtect[0], &m_OldVirtualProtect[1]);
		}
		else
		{
			result = *reinterpret_cast<T*>(Address);
		}
		return result;
	}

	// Restore any patch done with the restore flag enabled
	void RestorePatch();

	// Same as above, but instead, we apply an offset
	template <class T>
	inline T GetWithOffset(uint32_t m_Offset)
	{
		T result;
		DWORD m_OldVirtualProtect[2];

		if (bRequiresVirtualProtection)
		{
			VirtualProtect(reinterpret_cast<void*>(Address + m_Offset), sizeof(T), PAGE_EXECUTE_READWRITE, &m_OldVirtualProtect[0]);
			result = *reinterpret_cast<T*>(Address + m_Offset);
			VirtualProtect(reinterpret_cast<void*>(Address + m_Offset), sizeof(T), m_OldVirtualProtect[0], &m_OldVirtualProtect[1]);
		}
		else
		{
			result = *reinterpret_cast<T*>(Address + m_Offset);
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