#pragma once

#include <cstdint>
#include <Windows.h>
#include <vector>

/////////////// New code which uses operators for comparing, setting, and even adding, multiplying, and much more 
enum eMemoryBackupRestoreType
{
	BACKUP_NOTHING,
	BACKUP_OLD_JUMP_ADDRESS,
	BACKUP_OLD_CALL_ADDRESS,
};

class MemoryBackup
{
public:
	uint32_t m_dwOldAddress;
	void* m_dwOldValue; // TODO: change this?
	eMemoryBackupRestoreType m_eRestoreType;

	// For laziness sake
	MemoryBackup(uint32_t m_OldAddr, void* m_OldValue, eMemoryBackupRestoreType m_Type)
	{
		this->m_dwOldAddress = m_OldAddr;
		this->m_dwOldValue = m_OldValue;
		this->m_eRestoreType = m_Type;
	}

	MemoryBackup();
};

class Memory
{
private:
	uint32_t Address;

	bool bShouldStoreOriginal : 1; // When setting memory, keep the original value.
	bool bRequiresVirtualProtection : 1; // We need to override the current address permissions when using the operators

	std::vector<MemoryBackup> m_vMemoryBackupData;

public:
	Memory() { Address = 0; };
	Memory(uint32_t addr) { Address = addr; }

	// Sets the Memory struct's flags
	void SetFlags(bool bBackup, bool bVirtualProtect)
	{
		if (this->bShouldStoreOriginal && !bBackup)
		{
			for (uint32_t i = 0; i < this->m_vMemoryBackupData.size(); i++)
			{
				this->m_vMemoryBackupData.erase(this->m_vMemoryBackupData.begin() + i); // Let's erase the backup list as we do not need it
			}
		}

		this->bShouldStoreOriginal = bBackup;
		this->bRequiresVirtualProtection = bVirtualProtect;
	}

	// Adds a MemoryBackup to the list
	void AddBackup(MemoryBackup m_pBackup)
	{
		if (this->bShouldStoreOriginal)
		{
			this->m_vMemoryBackupData.push_back(m_pBackup);
		}
	}

	// Change address
	void ChangeAddress(uint32_t newAddr) { Address = newAddr; }

	// Sets memory value with protect parameter
	template <class T>
	inline void Set(T value, bool bProtect)
	{
		DWORD dwProtect[2];

		if (bProtect)
		{
			VirtualProtect((void*)this->Address, sizeof(T), PAGE_EXECUTE_READWRITE, &dwProtect[0]);
			*(T*)this->Address = value;
			VirtualProtect((void*)this->Address, sizeof(T), dwProtect[0], &dwProtect[1]);
		}
		else
		{
			*(T*)this->Address = value;
		}
	}

	// Gets memory value with virtual protect parameter
	template <class T>
	inline T Get(bool bProtect)
	{
		T result;
		DWORD dwProtect[2];

		if (bProtect)
		{
			VirtualProtect((LPVOID)this->Address, sizeof(T), PAGE_EXECUTE_READWRITE, &dwProtect[0]);
			result = *(T*)this->Address;
			VirtualProtect((LPVOID)this->Address, sizeof(T), dwProtect[0], &dwProtect[1]);
		}
		else
		{
			result = *(T*)this->Address;
		}
		return result;
	}

	// Returns the current address
	inline uint32_t GetAddress() { return this->Address; }

	// todo: finish this!!
	// Comparison

	template <class T>
	bool operator==(const T& rvalue) { return *(T*)this->Address == rvalue; }

	template <class T>
	bool operator>(const T& value) { return *(T*)this->Address > value; }
		
	template <class T>
	bool operator<(const T& value) { return *(T*)this->Address < value; }

	template <class T>
	bool operator>=(const T& value) { return *(T*)this->Address >= value; }

	template <class T>
	bool operator<=(const T& value) { return *(T*)this->Address <= value; }

	template <class T>
	bool operator!=(const T& value) { return *(T*)this->Address != value; }

	// Operators
	template <class T>
	void operator=(const T& value) { *(T*)this->Address = value; }

	template <class T>
	void operator+(const T& value) { *(T*)this->Address = *(T*)this->Address + value; }

	template <class T>
	void operator-(const T& value) { *(T*)this->Address = *(T*)this->Address - value; }

	template <class T>
	void operator*(const T& value) { *(T*)this->Address = *(T*)this->Address * value; }

	template <class T>
	void operator/(const T& value) { *(T*)this->Address = *(T*)this->Address / value; }
	void operator%(const int& value) { *(int*)this->Address = *(int*)this->Address % value; }

	template <class T>
	void operator+=(const T& value) { *(T*)this->Address += value; }

	template <class T>
	void operator-=(const T& value) { *(T*) this->Address -= value; }

	template <class T>
	void operator*=(const T& value) { *(T*) this->Address *= value; }

	template <class T>
	void operator/=(const T& value) { *(T*) this->Address /= value; }
	void operator%=(const int& value) { *(int*) this->Address %= value; }
};