#include "Shared.hpp"
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