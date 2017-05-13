#pragma once

#include <cstdint>
#include <Windows.h>
#include "Memory.h"

/////////////// General functions - no specific stuff here
class General
{
public:
	// Memcpy with virtual protect
	static void MemCpy(uint32_t dest, void* src, size_t size, bool bProtect = true);
	static void MemCpy(void* m_pDest, void* m_pSrc, size_t m_iSize, bool bProtect = true);
	static void MemCpy(Memory* m_pDest, void* m_pSrc, size_t m_iSize);

	// Memset with virtual protect
	static void MemSet(void* m_pDest, uint32_t m_nValue, size_t m_iSize, bool bProtect = true);
	static void MemSet(uint32_t m_pDest, uint32_t m_nValue, size_t m_iSize, bool bProtect = true);
	static void MemSet(Memory* m_pDest, uint32_t m_nValue, size_t m_iSize);

	// Strncpy with virtual protect
	static void StrNCpy(void* dest, char* src, size_t size, bool bProtect = true);
	static void StrNCpy(uint32_t dest, char* src, size_t size, bool bProtect = true);
	static void StrNCpy(Memory* m_pDest, char* src, size_t size);

	// Unprotect/protect functions
	static void ProtectMemory(uint32_t m_dwAddr, size_t m_iSize);
	static void ProtectMemory(Memory* m_dwAddr, size_t m_iSize);
	static void UnprotectMemory(uint32_t m_dwAddr, size_t m_iSize);
	static void UnprotectMemory(Memory* m_dwAddr, size_t m_iSize);
};
