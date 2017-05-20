#include "../Shared.hpp"
#include "RawHookVariable.h"
#include "TheRawHooks.h"

/*
	Constructs a RawHookVariable with a fixed size of 1 byte
*/
RawHookVariable::RawHookVariable(std::string m_Name, uint8_t m_Value)
{
	m_bValue = m_Value;
	m_szVariableName = m_Name;
	m_eType = RAWHOOKVARIABLE_BYTE;
	TheRawHooks::m_vVariables.push_back(this);
}

RawHookVariable::RawHookVariable(const char* szName, uint8_t value)
{
	m_bValue = value;
	m_szVariableName = szName;
	m_eType = RAWHOOKVARIABLE_BYTE;
	TheRawHooks::m_vVariables.push_back(this);
}

/*
	Constructs a RawHookVariable with a fixed size of 2 bytes
*/
RawHookVariable::RawHookVariable(std::string szName, uint16_t value)
{
	m_wValue = value;
	m_szVariableName = szName;
	m_eType = RAWHOOKVARIABLE_WORD;
	TheRawHooks::m_vVariables.push_back(this);
}

RawHookVariable::RawHookVariable(const char* szName, uint16_t value)
{
	m_wValue = value;
	m_szVariableName = szName;
	m_eType = RAWHOOKVARIABLE_WORD;
	TheRawHooks::m_vVariables.push_back(this);
}

/*
	Constructs a RawHookVariable with a fixed size of 4 bytes
*/
RawHookVariable::RawHookVariable(std::string szName, uint32_t value)
{
	m_dwValue = value;
	m_szVariableName = szName;
	m_eType = RAWHOOKVARIABLE_DWORD;
	TheRawHooks::m_vVariables.push_back(this);
}

RawHookVariable::RawHookVariable(const char* szName, uint32_t value)
{
	m_dwValue = value;
	m_szVariableName = szName;
	m_eType = RAWHOOKVARIABLE_DWORD;
	TheRawHooks::m_vVariables.push_back(this);
}

/*
	Constructs a RawHookVariable with a fixed size of 4 bytes, and as a float
*/
RawHookVariable::RawHookVariable(std::string szName, float value)
{
	m_fValue = value;
	m_szVariableName = szName;
	m_eType = RAWHOOKVARIABLE_FLOAT;
	TheRawHooks::m_vVariables.push_back(this);
}

RawHookVariable::RawHookVariable(const char* szName, float value)
{
	m_fValue = value;
	m_szVariableName = szName;
	m_eType = RAWHOOKVARIABLE_FLOAT;
	TheRawHooks::m_vVariables.push_back(this);
}

/*
	Destructs the RawHookVariable
*/
RawHookVariable::~RawHookVariable()
{
	// Cut out the destructed variable from the list of variables
	for (uint32_t i = 0; i < TheRawHooks::m_vVariables.size(); i++)
	{
		if (TheRawHooks::m_vVariables[i]->m_szVariableName == m_szVariableName)
		{
			TheRawHooks::m_vVariables.erase(TheRawHooks::m_vVariables.begin() + i);
		}
	}

	switch (m_eType)
	{
	case RAWHOOKVARIABLE_BYTE:
		m_bValue = 0;
		break;
	case RAWHOOKVARIABLE_WORD:
		m_wValue = 0;
		break;
	case RAWHOOKVARIABLE_DWORD:
		m_dwValue = 0;
		break;
	case RAWHOOKVARIABLE_FLOAT:
		m_fValue = 0.0f;
		break;
	}
	m_eType = RAWHOOKVARIABLE_UNKNOWN_TYPE;
	m_szVariableName = "UNDEFINED";
}