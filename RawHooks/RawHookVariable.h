#pragma once

#include <stdint.h>
#include <string>

class RawHookVariable
{
private:
	uint32_t m_nValue;
	std::string m_szVariableName;

public:
	RawHookVariable(const std::string m_Name, uint32_t m_Value);
	~RawHookVariable();
};
