#include "../Shared.hpp"
#include "RawHookVariable.h"
#include "TheRawHooks.h"

RawHookVariable::RawHookVariable(const std::string m_Name, uint32_t m_Value)
{
	this->m_nValue = m_Value;
	this->m_szVariableName = m_Name;
	TheRawHooks::m_vVariables.push_back(this);
}

RawHookVariable::~RawHookVariable()
{
	// Try and cut out the destructed variable from the list of variables
	for (uint32_t i = 0; i < TheRawHooks::m_vVariables.size(); i++)
	{
		if (TheRawHooks::m_vVariables[i]->m_szVariableName == this->m_szVariableName)
		{
			TheRawHooks::m_vVariables.erase(TheRawHooks::m_vVariables.begin() + i);
		}
	}

	this->m_nValue = 0;
	this->m_szVariableName = "UNDEFINED";
}