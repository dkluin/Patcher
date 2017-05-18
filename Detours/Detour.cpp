#include "../Shared.hpp"
#include "Detour.h"
#include "../Injecting.h"

Detour::Detour(void* m_pOriginal, void* m_pDetoured)
{
	m_pOriginalFunction = m_pOriginal;
	m_pDetouredFunction = m_pDetoured;

	Address = reinterpret_cast<uint32_t>(m_pOriginal);
	bRequiresVirtualProtection = true;
	bShouldStoreOriginal = true;
}

Detour::Detour(std::string m_szOriginalName, std::string m_szDetouredName)
{
	m_szOriginalFunctionName = m_szOriginalName;
	m_szDetouredFunctionName = m_szOriginalName;

	bRequiresVirtualProtection = true;
	bShouldStoreOriginal = true;
}

Detour::~Detour()
{
	if (m_bApplied)
	{
		UndoDetour();
	}
}

void Detour::ApplyDetour()
{
	if (!m_bApplied)
	{
		m_bApplied = true;
	}
}

void Detour::UndoDetour()
{
	if (m_bApplied)
	{

	}
}