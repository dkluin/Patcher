#include "RawHookVariable.h"

RawHookVariable::RawHookVariable(const std::string m_Name, uint32_t m_Value)
{
	this->m_nValue = m_Value;
	this->m_szVariableName = m_Name;
}

RawHookVariable::~RawHookVariable()
{
	this->m_nValue = 0;
	this->m_szVariableName = "UNDEFINED";
}