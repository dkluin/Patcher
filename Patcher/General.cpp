#include "Shared.hpp"
#include "General.h"

/*
	General

	These functions are wrappers around the well-known C functions (memcpy, memset...)
	to allow them to both support restorable patching through Memory class instances, and use WINAPI's virtual protect feature.
*/

void General::MemCpy(Memory* m_pDest, void* m_pSrc, size_t m_iSize)
{
	DWORD m_OldVirtualProtect[2];

	if (m_pDest->GetVirtualProtect())
	{
		VirtualProtect(reinterpret_cast<void*>(m_pDest->GetAddress()), m_iSize, PAGE_EXECUTE_READWRITE, &m_OldVirtualProtect[0]);
		memcpy(reinterpret_cast<void*>(m_pDest->GetAddress()), m_pSrc, m_iSize);
		VirtualProtect(reinterpret_cast<void*>(m_pDest->GetAddress()), m_iSize, m_OldVirtualProtect[0], &m_OldVirtualProtect[1]);
	}
	else
	{
		memcpy(reinterpret_cast<void*>(m_pDest->GetAddress()), m_pSrc, m_iSize);
	}
}

// Wrapper around strncpy to allow access with virtual protection
void General::StrNCpy(Memory* m_pDest, char* src, size_t size)
{
	DWORD m_OldVirtualProtect[2];

	if (m_pDest->GetVirtualProtect())
	{
		VirtualProtect(reinterpret_cast<void*>(m_pDest->GetAddress()), size, PAGE_EXECUTE_READWRITE, &m_OldVirtualProtect[0]);
		strncpy(reinterpret_cast<char*>(m_pDest->GetAddress()), src, size);
		VirtualProtect(reinterpret_cast<void*>(m_pDest->GetAddress()), size, m_OldVirtualProtect[0], &m_OldVirtualProtect[1]);
	}
	else
	{
		strncpy(reinterpret_cast<char*>(m_pDest->GetAddress()), src, size);
	}
}

void General::MemSet(Memory* m_pDest, uint32_t m_nValue, size_t m_iSize)
{
	DWORD m_OldVirtualProtect[2];

	if (m_pDest->GetVirtualProtect())
	{
		VirtualProtect(reinterpret_cast<void*>(m_pDest->GetAddress()), m_iSize, PAGE_EXECUTE_READWRITE, &m_OldVirtualProtect[0]);
		memset(reinterpret_cast<void*>(m_pDest->GetAddress()), m_nValue, m_iSize);
		VirtualProtect(reinterpret_cast<void*>(m_pDest->GetAddress()), m_iSize, m_OldVirtualProtect[0], &m_OldVirtualProtect[1]);
	}
	else
	{
		memset(reinterpret_cast<void*>(m_pDest->GetAddress()), m_nValue, m_iSize);
	}
}