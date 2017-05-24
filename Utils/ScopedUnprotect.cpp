#include "../Shared.hpp"
#include "ScopedUnprotect.h"

ScopedUnprotect::ScopedUnprotect(Memory* pStartMemory, size_t iSizeOfMemory)
{
	if (pStartMemory)
	{
		m_pMemory = pStartMemory;
		m_iSizeOfMemory = iSizeOfMemory;
		m_bUseMemoryClass = true;
		VirtualProtect(reinterpret_cast<void*>(m_pMemory->GetAddress()), m_iSizeOfMemory, PAGE_EXECUTE_READWRITE, &m_dwOldVirtualProtect[0]);
	}
}

ScopedUnprotect::ScopedUnprotect(uint32_t dwAddress, size_t iSizeOfMemory)
{
	if (dwAddress)
	{
		m_Address = dwAddress;
		m_iSizeOfMemory = iSizeOfMemory;
		m_bUseMemoryClass = true;
		VirtualProtect(reinterpret_cast<void*>(m_pMemory->GetAddress()), m_iSizeOfMemory, PAGE_EXECUTE_READWRITE, &m_dwOldVirtualProtect[0]);
	}
}

ScopedUnprotect::~ScopedUnprotect()
{
	if (m_bUseMemoryClass)
	{
		if (m_pMemory)
		{
			VirtualProtect(reinterpret_cast<void*>(m_pMemory->GetAddress()), m_iSizeOfMemory, m_dwOldVirtualProtect[0], &m_dwOldVirtualProtect[1]);
		}
	}
	else
	{
		VirtualProtect(reinterpret_cast<void*>(m_Address), m_iSizeOfMemory, m_dwOldVirtualProtect[0], &m_dwOldVirtualProtect[1]);
	}
}