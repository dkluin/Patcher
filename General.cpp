#include "Shared.hpp"
#include "General.h"

// memcpy with memory protection

void General::MemCpy(uint32_t dest, void* src, size_t size, bool bProtect)
{
	DWORD dwProtect[2];

	if (bProtect)
	{
		VirtualProtect((void*)dest, size, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
		memcpy((void*)dest, src, size);
		VirtualProtect((void*)dest, size, dwProtect[0], &dwProtect[1]);
	}
	else
	{
		memcpy((void*)dest, src, size);
	}
}

void General::MemCpy(void* m_pDest, void* m_pSrc, size_t m_iSize, bool bProtect)
{
	DWORD dwProtect[2];

	if (bProtect)
	{
		VirtualProtect(m_pDest, m_iSize, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
		memcpy(m_pDest, m_pSrc, m_iSize);
		VirtualProtect(m_pDest, m_iSize, dwProtect[0], &dwProtect[1]);
	}
	else
	{
		memcpy(m_pDest, m_pSrc, m_iSize);
	}
}

void General::MemCpy(Memory* m_pDest, void* m_pSrc, size_t m_iSize)
{
	DWORD dwProtect[2];

	if (m_pDest->GetVirtualProtect())
	{
		VirtualProtect((void*)m_pDest->GetAddress(), m_iSize, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
		memcpy((void*)m_pDest->GetAddress(), m_pSrc, m_iSize);
		VirtualProtect((void*)m_pDest->GetAddress(), m_iSize, dwProtect[0], &dwProtect[1]);
	}
	else
	{
		memcpy((void*)m_pDest->GetAddress(), m_pSrc, m_iSize);
	}
}

// strncpy with memory protection
void General::StrNCpy(void* dest, char* src, size_t size, bool bProtect)
{
	DWORD dwProtect[2];
	
	if (bProtect)
	{
		VirtualProtect(dest, size, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
		strncpy((char*)dest, src, size);
		VirtualProtect(dest, size, dwProtect[0], &dwProtect[1]);
	}
	else
	{
		strncpy((char*)dest, src, size);
	}
}

void General::StrNCpy(uint32_t dest, char* src, size_t size, bool bProtect)
{
	DWORD dwProtect[2];

	if (bProtect)
	{
		VirtualProtect((void*)dest, size, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
		strncpy((char*)dest, src, size);
		VirtualProtect((void*)dest, size, dwProtect[0], &dwProtect[1]);
	}
	else
	{
		strncpy((char*)dest, src, size);
	}
}

void General::StrNCpy(Memory* m_pDest, char* src, size_t size)
{
	DWORD dwProtect[2];

	if (m_pDest->GetVirtualProtect())
	{
		VirtualProtect((void*)m_pDest->GetAddress(), size, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
		strncpy((char*)m_pDest->GetAddress(), src, size);
		VirtualProtect((void*)m_pDest->GetAddress(), size, dwProtect[0], &dwProtect[1]);
	}
	else
	{
		strncpy((char*)m_pDest->GetAddress(), src, size);
	}
}

void General::MemSet(void* m_pDest, uint32_t m_nValue, size_t m_iSize, bool bProtect)
{
	DWORD dwProtect[2];

	if (bProtect)
	{
		VirtualProtect(m_pDest, m_iSize, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
		memset(m_pDest, m_nValue, m_iSize);
		VirtualProtect(m_pDest, m_iSize, dwProtect[0], &dwProtect[1]);
	}
	else
	{
		memset(m_pDest, m_nValue, m_iSize);
	}
}

void General::MemSet(uint32_t m_pDest, uint32_t m_nValue, size_t m_iSize, bool bProtect)
{
	DWORD dwProtect[2];

	if (bProtect)
	{
		VirtualProtect((void*)m_pDest, m_iSize, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
		memset((void*)m_pDest, m_nValue, m_iSize);
		VirtualProtect((void*)m_pDest, m_iSize, dwProtect[0], &dwProtect[1]);
	}
	else
	{
		memset((void*)m_pDest, m_nValue, m_iSize);
	}
}

void General::MemSet(Memory* m_pDest, uint32_t m_nValue, size_t m_iSize)
{
	DWORD dwProtect[2];

	if (m_pDest->GetVirtualProtect())
	{
		VirtualProtect((void*)m_pDest->GetAddress(), m_iSize, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
		memset((void*)m_pDest->GetAddress(), m_nValue, m_iSize);
		VirtualProtect((void*)m_pDest->GetAddress(), m_iSize, dwProtect[0], &dwProtect[1]);
	}
	else
	{
		memset((void*)m_pDest->GetAddress(), m_nValue, m_iSize);
	}
}

void General::ProtectMemory(uint32_t m_dwAddr, size_t m_iSize)
{
	DWORD m_dwOldProtection;
	VirtualProtect((void*)m_dwAddr, m_iSize, PAGE_EXECUTE, &m_dwOldProtection);
}

void General::ProtectMemory(Memory* m_dwAddr, size_t m_iSize)
{
	DWORD m_dwOldProtection;
	VirtualProtect((void*)m_dwAddr->GetAddress(), m_iSize, PAGE_EXECUTE, &m_dwOldProtection);
}

void General::UnprotectMemory(uint32_t m_dwAddr, size_t m_iSize)
{
	DWORD m_dwOldProtection;
	VirtualProtect((void*)m_dwAddr, m_iSize, PAGE_EXECUTE_READWRITE, &m_dwOldProtection);
}

void General::UnprotectMemory(Memory* m_dwAddr, size_t m_iSize)
{
	DWORD m_dwOldProtection;
	VirtualProtect((void*)m_dwAddr->GetAddress(), m_iSize, PAGE_EXECUTE_READWRITE, &m_dwOldProtection);
}