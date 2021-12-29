#include "../Shared.hpp"
#include "RawHook.h"
#include "TheRawHooks.h"
#include "../General.h"
#include "../Injecting.h"

RawHook::RawHook(uint32_t m_dwJumpFrom, uint32_t m_dwJumpTo)
{
	m_dwJumpedFromAddr = m_dwJumpFrom;
	m_dwJumpOutAddr = m_dwJumpTo;
	m_bFinished = false;
	m_bStarted = false;
}

void RawHook::Write(const void* m_nData, size_t m_iSize)
{
	memcpy(TheRawHooks::ms_pTheRawHooks + TheRawHooks::ms_nGlobalPos, m_nData, m_iSize);
	TheRawHooks::ms_nGlobalPos += m_iSize;
}

void RawHook::MakeRawJMP(uint32_t m_dwReturnAddr)
{
	MemoryInjector::MakeJMP((uint32_t)TheRawHooks::ms_pTheRawHooks + TheRawHooks::ms_nGlobalPos, m_dwReturnAddr, true); 
	TheRawHooks::ms_nGlobalPos += 5;
}

void RawHook::MakeRawCALL(uint32_t m_dwReturnAddr)
{
	MemoryInjector::MakeCALL((uint32_t)TheRawHooks::ms_pTheRawHooks + TheRawHooks::ms_nGlobalPos, m_dwReturnAddr, true);
	TheRawHooks::ms_nGlobalPos += 5;
}

void RawHook::Finish()
{
	if (m_bStarted && !m_bFinished)
	{
		MakeRawJMP(m_dwJumpOutAddr);
		Write("\x90\x90", 2);

		// Write a JMP instruction on the specified address to the starting position
		MemoryInjector::MakeJMP(m_dwJumpedFromAddr, TheRawHooks::ms_pTheRawHooks + m_dwPositionOnStart, true);
		m_bFinished = true;
	}
}

void RawHook::MakeRawRET()
{
	MemoryInjector::MakeRET(reinterpret_cast<uint32_t>(TheRawHooks::ms_pTheRawHooks) + TheRawHooks::ms_nGlobalPos, true);
	TheRawHooks::ms_nGlobalPos += 1;
}

void RawHook::Start()
{
	if (!m_bStarted)
	{
		m_dwPositionOnStart = TheRawHooks::ms_nGlobalPos + sizeof(uint16_t);
		Write("\x90\x90", 2);
		m_bStarted = true;
	}
}

void RawHook::WriteVariable(std::string m_szVariableName)
{
	for (uint32_t i = 0; i < TheRawHooks::m_vVariables.size(); i++)
	{
		if (TheRawHooks::m_vVariables[i]->GetVariableName() == m_szVariableName)
		{
			switch (TheRawHooks::m_vVariables[i]->m_eType)
			{
			case RAWHOOKVARIABLE_BYTE:
				Write(static_cast<const void*>(&TheRawHooks::m_vVariables[i]->m_bValue), sizeof(uint8_t));
				break;
			case RAWHOOKVARIABLE_WORD:
				Write(static_cast<const void*>(&TheRawHooks::m_vVariables[i]->m_wValue), sizeof(uint16_t));
				break;
			case RAWHOOKVARIABLE_DWORD:
				Write(static_cast<const void*>(&TheRawHooks::m_vVariables[i]->m_dwValue), sizeof(uint32_t));
				break;
			case RAWHOOKVARIABLE_FLOAT:
				Write(static_cast<const void*>(&TheRawHooks::m_vVariables[i]->m_fValue), sizeof(float));
				break;
			}
		}
	}
}

void RawHook::WriteVariable(RawHookVariable* m_pVar)
{
	switch (m_pVar->m_eType)
	{
	case RAWHOOKVARIABLE_BYTE:
		Write(static_cast<const void*>(&m_pVar->m_bValue), sizeof(uint8_t));
		break;
	case RAWHOOKVARIABLE_WORD:
		Write(static_cast<const void*>(&m_pVar->m_wValue), sizeof(uint16_t));
		break;
	case RAWHOOKVARIABLE_DWORD:
		Write(static_cast<const void*>(&m_pVar->m_dwValue), sizeof(uint32_t));
		break;
	case RAWHOOKVARIABLE_FLOAT:
		Write(static_cast<const void*>(&m_pVar->m_fValue), sizeof(float));
		break;
	}
}