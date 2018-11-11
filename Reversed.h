#pragma once

#include "Shared.hpp"
#include <vector>

class ReversedFunctionInfo;

class Reversed
{
	friend ReversedFunctionInfo;

private:
	static std::vector<ReversedFunctionInfo> ms_vReversedFunctions;

public:
	static void CheckIfAddressIsInRange(uint32_t dwAddress);
};

class ReversedFunctionInfo
{
public:
	uint32_t m_dwStartAddress, m_dwEndAddress;

	ReversedFunctionInfo() { m_dwStartAddress = 0; m_dwEndAddress = 0; }
	ReversedFunctionInfo(uint32_t dwStart, uint32_t dwEnd);
};