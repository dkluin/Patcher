#pragma once

#include "Shared.hpp"
#include <vector>

class ReversedFunctionInfo;

class Reversed
{
	friend ReversedFunctionInfo;

private:
	static std::vector<ReversedFunctionInfo> ms_vReversedFunctions;
	static FILE* ms_pFile;
	static bool ms_bLoggingOverlappingPatches;
	static int ms_nDetectedMatches;

public:
	static void CheckIfAddressIsInRange(uint32_t dwAddress);
	static void StartLogging();
	static void StopLogging();
};

class ReversedFunctionInfo
{
public:
	uint32_t m_dwStartAddress, m_dwEndAddress;
	char m_szFunctionName[250];

	ReversedFunctionInfo() { m_dwStartAddress = 0; m_dwEndAddress = 0; memset(m_szFunctionName, 0, sizeof(m_szFunctionName)); }
	ReversedFunctionInfo(char* szFunctionName, uint32_t dwStart, uint32_t dwEnd);
};