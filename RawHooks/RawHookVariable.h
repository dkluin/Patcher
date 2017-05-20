#pragma once

#include <stdint.h>
#include <string>
#include <vector>

enum eRawHookVariableType
{
	RAWHOOKVARIABLE_UNKNOWN_TYPE = -1,
	RAWHOOKVARIABLE_BYTE,
	RAWHOOKVARIABLE_WORD,
	RAWHOOKVARIABLE_DWORD,
	RAWHOOKVARIABLE_FLOAT
};

class RawHookVariable
{
public:
	friend class TheRawHooks;
	friend class RawHook;

	union
	{
		uint8_t m_bValue;
		uint16_t m_wValue;
		uint32_t m_dwValue;
		float m_fValue;
	};
	eRawHookVariableType m_eType;

	std::string m_szVariableName;
	bool m_bShouldUseVector;

public:
	/*
		Default constructor
	*/
	RawHookVariable()
	{
		m_eType = RAWHOOKVARIABLE_UNKNOWN_TYPE;
		m_szVariableName = "UNDEFINED";
	}

	/*
		Constructs a RawHookVariable with a fixed size of 1 byte
	*/
	RawHookVariable(std::string m_Name, uint8_t m_Value);
	RawHookVariable(const char* szName, uint8_t value);

	/*
		Constructs a RawHookVariable with a fixed size of 2 bytes
	*/
	RawHookVariable(std::string szName, uint16_t value);
	RawHookVariable(const char* szName, uint16_t value);

	/*
		Constructs a RawHookVariable with a fixed size of 4 bytes
	*/
	RawHookVariable(std::string szName, uint32_t value);
	RawHookVariable(const char* szName, uint32_t value);

	/*
		Constructs a RawHookVariable with a fixed size of 4 bytes, and as a float
	*/
	RawHookVariable(std::string szName, float value);
	RawHookVariable(const char* szName, float value);

	/*
		Destructs a RawHookVariable
	*/
	~RawHookVariable();

	/*
		Other member functions
	*/
	std::string GetVariableName()
	{
		return m_szVariableName;
	}

	bool ShouldUseVector()
	{
		return m_bShouldUseVector;
	}
};
