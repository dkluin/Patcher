#pragma once

#include <cstdint>
#include <Windows.h>
#include "Memory.h"

/*
	General

	Anything really. Wrappers around C functions, and more.
*/

class General
{
public:
	// Memcpy with virtual protect
	static inline void MemCpy(uint32_t dest, void* src, size_t size, bool bProtect = true)
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

	static inline void MemCpy(void* m_pDest, void* m_pSrc, size_t m_iSize, bool bProtect = true)
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

	static void MemCpy(Memory* m_pDest, void* m_pSrc, size_t m_iSize);

	// Memset with virtual protect
	static inline void MemSet(void* m_pDest, uint32_t m_nValue, size_t m_iSize, bool bProtect = true)
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

	static inline void MemSet(uint32_t m_pDest, uint32_t m_nValue, size_t m_iSize, bool bProtect = true)
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

	static void MemSet(Memory* m_pDest, uint32_t m_nValue, size_t m_iSize);

	// Strncpy with virtual protect
	static inline void StrNCpy(void* dest, char* src, size_t size, bool bProtect = true)
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

	static inline void StrNCpy(uint32_t dest, char* src, size_t size, bool bProtect = true)
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

	static void StrNCpy(Memory* m_pDest, char* src, size_t size);

	// Memcmp with virtual protect
	static inline int MemCmp(void* pBuffer1, void* pBuffer2, size_t iSize, bool bProtect = true)
	{
		DWORD m_OldVirtualProtect[2];

		if (bProtect)
		{
			VirtualProtect(pBuffer1, iSize, PAGE_EXECUTE_READWRITE, &m_OldVirtualProtect[0]);
			int result = memcmp(pBuffer1, pBuffer2, iSize);
			VirtualProtect(pBuffer1, iSize, m_OldVirtualProtect[0], &m_OldVirtualProtect[1]);
			return result;
		}
		else
		{
			return memcmp(pBuffer1, pBuffer2, iSize);
		}
	}

	// Unprotect/protect functions
	static inline DWORD MemoryProtect(uint32_t dwAddr, DWORD dwNewVirtualProtect, PDWORD dwOldVirtualProtect, size_t iSize)
	{
		return VirtualProtect(reinterpret_cast<void*>(dwAddr), iSize, dwNewVirtualProtect, dwOldVirtualProtect);
	}

	static inline DWORD MemoryProtect(Memory* dwAddr, DWORD dwNewVirtualProtect, PDWORD dwOldVirtualProtect, size_t iSize)
	{
		return VirtualProtect(reinterpret_cast<void*>(dwAddr->GetAddress()), iSize, dwNewVirtualProtect, dwOldVirtualProtect);
	}
};
