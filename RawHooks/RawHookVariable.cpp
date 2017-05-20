/*
	RawHookVariable.cpp

	Nothing more than unfinished code at this point, but it is in an useable state - except that its still not fully implemented

	TODO:
	- Memory support
	- Refactoring
	- Wrapper functions which create a RawHook but iterate through the data and place variables where needed, see TheRawHooks::StaticRawHook
	- Better destructors which finish the RawHook if not done so when the instance goes out of scope
	- Improved RawHookVariable which uses templates?
*/

#include "../Shared.hpp"
#include "RawHookVariable.h"
#include "TheRawHooks.h"

RawHookVariable::RawHookVariable(const std::string m_Name, uint32_t m_Value)
{
	m_nValue = m_Value;
	m_szVariableName = m_Name;
	TheRawHooks::m_vVariables.push_back(this);
}

RawHookVariable::~RawHookVariable()
{
	// Try and cut out the destructed variable from the list of variables
	for (uint32_t i = 0; i < TheRawHooks::m_vVariables.size(); i++)
	{
		if (TheRawHooks::m_vVariables[i]->m_szVariableName == m_szVariableName)
		{
			TheRawHooks::m_vVariables.erase(TheRawHooks::m_vVariables.begin() + i);
		}
	}

	m_nValue = 0;
	m_szVariableName = "UNDEFINED";
}