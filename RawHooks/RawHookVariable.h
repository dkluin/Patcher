/*
	RawHookVariable.h

	Nothing more than unfinished code at this point, but it is in an useable state - except that its still not fully implemented

	TODO:
	- Memory support
	- Refactoring
	- Wrapper functions which create a RawHook but iterate through the data and place variables where needed, see TheRawHooks::StaticRawHook
	- Better destructors which finish the RawHook if not done so when the instance goes out of scope
	- Improved RawHookVariable which uses templates?
*/

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
