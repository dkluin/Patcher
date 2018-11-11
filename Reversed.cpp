#include "Shared.hpp"
#include "Reversed.h"

std::vector<ReversedFunctionInfo> Reversed::ms_vReversedFunctions;

void Reversed::CheckIfAddressIsInRange(uint32_t dwAddress)
{
#ifdef PATCHER_DEVELOPMENT_BUILD
	for (size_t i = 0; i < ms_vReversedFunctions.size(); i++)
	{
		if (dwAddress >= ms_vReversedFunctions.at(i).m_dwStartAddress && dwAddress <= ms_vReversedFunctions.at(i).m_dwEndAddress)
		{
			PatcherPrintMessageBox("Patch at address 0x%X overlaps with reversed function between 0x%X and 0x%X", dwAddress, ms_vReversedFunctions.at(i), ms_vReversedFunctions.at(i).m_dwEndAddress);
		}
	}
#endif
}

ReversedFunctionInfo::ReversedFunctionInfo(uint32_t dwStart, uint32_t dwEnd)
{
	m_dwStartAddress = dwStart;
	m_dwEndAddress = dwEnd;

#ifdef PATCHER_DEVELOPMENT_BUILD
	Reversed::ms_vReversedFunctions.push_back(*this);
#endif
}