#include "Shared.hpp"
#include "Reversed.h"

std::vector<ReversedFunctionInfo> Reversed::ms_vReversedFunctions;
FILE* Reversed::ms_pFile = nullptr;
bool Reversed::ms_bLoggingOverlappingPatches = false;
int Reversed::ms_nDetectedMatches = 0;

void Reversed::CheckIfAddressIsInRange(uint32_t dwAddress)
{
#ifdef PATCHER_DEVELOPMENT_BUILD
	for (size_t i = 0; i < ms_vReversedFunctions.size(); i++)
	{
		if (dwAddress >= ms_vReversedFunctions.at(i).m_dwStartAddress && dwAddress <= ms_vReversedFunctions.at(i).m_dwEndAddress)
		{
			if (ms_bLoggingOverlappingPatches)
			{
				//fprintf(ms_pFile, "Possible patch at address 0x%X overlaps with reversed function named %s (between 0x%X and 0x%X)\n", dwAddress, ms_vReversedFunctions.at(i).m_szFunctionName, ms_vReversedFunctions.at(i).m_dwStartAddress, ms_vReversedFunctions.at(i).m_dwEndAddress);
				ms_nDetectedMatches++;
			}
		}
	}
#endif
}

void Reversed::StartLogging()
{
#ifdef PATCHER_DEVELOPMENT_BUILD
	if (!ms_bLoggingOverlappingPatches)
	{
		//ms_pFile = fopen("overlapping_patches.log", "w");
		ms_bLoggingOverlappingPatches = true;
	}
#endif
}

void Reversed::StopLogging()
{
#ifdef PATCHER_DEVELOPMENT_BUILD
	if (ms_bLoggingOverlappingPatches)
	{
		//fclose(ms_pFile);
		ms_bLoggingOverlappingPatches = false;

		//PatcherPrintMessageBox("Stopped detecting overlapping patches - %d matches found and saved to overlapping_patches.log", ms_nDetectedMatches);

		ms_nDetectedMatches = 0;
	}
#endif
}


ReversedFunctionInfo::ReversedFunctionInfo(char* szFunctionName, uint32_t dwStart, uint32_t dwEnd)
{
	strcpy(m_szFunctionName, szFunctionName);
	m_dwStartAddress = dwStart;
	m_dwEndAddress = dwEnd;

#ifdef PATCHER_DEVELOPMENT_BUILD
	Reversed::ms_vReversedFunctions.push_back(*this);
#endif
}