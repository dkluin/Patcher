#include "Shared.hpp"
#include "General.h"

/*
	General

	These functions are wrappers around the well-known C functions (memcpy, memset...)
	to allow them to both support restorable patching through Memory class instances, and use WINAPI's virtual protect feature.
*/

void General::MemCpy(uint32_t dest, void* src, size_t size, bool bProtect)
{
	DWORD m_OldVirtualProtect[2];

	if (bProtect)
	{
		VirtualProtect(reinterpret_cast<void*>(dest), size, PAGE_EXECUTE_READWRITE, &m_OldVirtualProtect[0]);
		memcpy(reinterpret_cast<void*>(dest), src, size);
		VirtualProtect(reinterpret_cast<void*>(dest), size, m_OldVirtualProtect[0], &m_OldVirtualProtect[1]);
	}
	else
	{
		memcpy(reinterpret_cast<void*>(dest), src, size);
	}
}

void General::MemCpy(void* m_pDest, void* m_pSrc, size_t m_iSize, bool bProtect)
{
	DWORD m_OldVirtualProtect[2];

	if (bProtect)
	{
		VirtualProtect(m_pDest, m_iSize, PAGE_EXECUTE_READWRITE, &m_OldVirtualProtect[0]);
		memcpy(m_pDest, m_pSrc, m_iSize);
		VirtualProtect(m_pDest, m_iSize, m_OldVirtualProtect[0], &m_OldVirtualProtect[1]);
	}
	else
	{
		memcpy(m_pDest, m_pSrc, m_iSize);
	}
}

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

// strncpy with memory protection
void General::StrNCpy(void* dest, char* src, size_t size, bool bProtect)
{
	DWORD m_OldVirtualProtect[2];
	
	if (bProtect)
	{
		VirtualProtect(dest, size, PAGE_EXECUTE_READWRITE, &m_OldVirtualProtect[0]);
		strncpy(reinterpret_cast<char*>(dest), src, size);
		VirtualProtect(dest, size, m_OldVirtualProtect[0], &m_OldVirtualProtect[1]);
	}
	else
	{
		strncpy(reinterpret_cast<char*>(dest), src, size);
	}
}

void General::StrNCpy(uint32_t dest, char* src, size_t size, bool bProtect)
{
	DWORD m_OldVirtualProtect[2];

	if (bProtect)
	{
		VirtualProtect(reinterpret_cast<void*>(dest), size, PAGE_EXECUTE_READWRITE, &m_OldVirtualProtect[0]);
		strncpy(reinterpret_cast<char*>(dest), src, size);
		VirtualProtect(reinterpret_cast<void*>(dest), size, m_OldVirtualProtect[0], &m_OldVirtualProtect[1]);
	}
	else
	{
		strncpy(reinterpret_cast<char*>(dest), src, size);
	}
}

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

void General::MemSet(void* m_pDest, uint32_t m_nValue, size_t m_iSize, bool bProtect)
{
	DWORD m_OldVirtualProtect[2];

	if (bProtect)
	{
		VirtualProtect(m_pDest, m_iSize, PAGE_EXECUTE_READWRITE, &m_OldVirtualProtect[0]);
		memset(m_pDest, m_nValue, m_iSize);
		VirtualProtect(m_pDest, m_iSize, m_OldVirtualProtect[0], &m_OldVirtualProtect[1]);
	}
	else
	{
		memset(m_pDest, m_nValue, m_iSize);
	}
}

void General::MemSet(uint32_t m_pDest, uint32_t m_nValue, size_t m_iSize, bool bProtect)
{
	DWORD m_OldVirtualProtect[2];

	if (bProtect)
	{
		VirtualProtect(reinterpret_cast<void*>(m_pDest), m_iSize, PAGE_EXECUTE_READWRITE, &m_OldVirtualProtect[0]);
		memset(reinterpret_cast<void*>(m_pDest), m_nValue, m_iSize);
		VirtualProtect(reinterpret_cast<void*>(m_pDest), m_iSize, m_OldVirtualProtect[0], &m_OldVirtualProtect[1]);
	}
	else
	{
		memset(reinterpret_cast<void*>(m_pDest), m_nValue, m_iSize);
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

DWORD General::ProtectMemory(uint32_t m_dwAddr, size_t m_iSize)
{
	DWORD m_dwOldProtection;
	VirtualProtect(reinterpret_cast<void*>(m_dwAddr), m_iSize, PAGE_EXECUTE, &m_dwOldProtection);
	return m_dwOldProtection;
}

DWORD General::ProtectMemory(Memory* m_dwAddr, size_t m_iSize)
{
	DWORD m_dwOldProtection;
	VirtualProtect(reinterpret_cast<void*>(m_dwAddr->GetAddress()), m_iSize, PAGE_EXECUTE, &m_dwOldProtection);
	return m_dwOldProtection;
}

DWORD General::UnprotectMemory(uint32_t m_dwAddr, size_t m_iSize)
{
	DWORD m_dwOldProtection;
	VirtualProtect(reinterpret_cast<void*>(m_dwAddr), m_iSize, PAGE_EXECUTE_READWRITE, &m_dwOldProtection);
	return m_dwOldProtection;
}

DWORD General::UnprotectMemory(Memory* m_dwAddr, size_t m_iSize)
{
	DWORD m_dwOldProtection;
	VirtualProtect(reinterpret_cast<void*>(m_dwAddr->GetAddress()), m_iSize, PAGE_EXECUTE_READWRITE, &m_dwOldProtection);
	return m_dwOldProtection;
}