#pragma once

#include <stdint.h>
#include <string>

class RawHookVariable
{
private:
	uint32_t m_nValue;
	std::string m_szVariableName;
	bool m_bShouldUseVector;

public:
	RawHookVariable(const std::string m_Name, uint32_t m_Value);
	~RawHookVariable();

	std::string GetVariableName()
	{
		return m_szVariableName;
	}

	bool ShouldUseVector()
	{
		return m_bShouldUseVector;
	}

	uint32_t GetVariableValue()
	{
		return m_nValue;
	}
};
