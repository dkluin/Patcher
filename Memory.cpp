#include "Memory.h"

Memory::Memory(Memory* m_pMemory)
{
	if (m_pMemory)
	{
		Address = m_pMemory->Address;
		bOldVirtualProtect = m_pMemory->bOldVirtualProtect;
		bRequiresVirtualProtection = m_pMemory->bRequiresVirtualProtection;
		bShouldStoreOriginal = m_pMemory->bShouldStoreOriginal;
		m_Type = m_pMemory->m_Type;
	}
}

template <class T>
void Memory::Set(T value)
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

template <class T>
T Memory::Get()
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