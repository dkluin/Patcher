#include "../Shared.hpp"
#include "RawHook.h"
#include "TheRawHooks.h"
#include "../General.h"
#include "../Injecting.h"


RawHook::RawHook(uint32_t m_dwJumpFrom, uint32_t m_dwJumpTo)
{
	this->m_dwJumpedFromAddr = m_dwJumpFrom;
	this->m_dwJumpOutAddr = m_dwJumpTo;
	this->m_bFinished = false;
	this->m_bStarted = false;
}

RawHook::~RawHook()
{

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
	if (this->m_bStarted && !this->m_bFinished)
	{
		this->MakeRawJMP(this->m_dwJumpOutAddr);
		this->Write("\x90\x90", 2);

		// Write a JMP instruction on the specified address to the starting position
		MemoryInjector::MakeJMP(this->m_dwJumpedFromAddr, TheRawHooks::ms_pTheRawHooks + this->m_dwPositionOnStart, true);
		this->m_bFinished = true;
	}
}

void RawHook::Start()
{
	if (!this->m_bStarted)
	{
		this->m_dwPositionOnStart = TheRawHooks::ms_nGlobalPos + sizeof(uint16_t);
		this->Write("\x90\x90", 2);
		this->m_bStarted = true;
	}
}

void RawHook::WriteIntVariable(std::string m_szVariableName)
{
	for (uint32_t i = 0; i < TheRawHooks::m_vVariables.size(); i++)
	{
		if (TheRawHooks::m_vVariables[i]->GetVariableName() == m_szVariableName)
		{
			uint32_t value = TheRawHooks::m_vVariables[i]->GetVariableValue();
			this->Write(static_cast<const void*>(&value), sizeof(uint32_t));
		}
	}
}

void RawHook::WriteIntVariable(RawHookVariable* m_pVar)
{
	uint32_t value = m_pVar->GetVariableValue();
	this->Write(static_cast<const void*>(&value), sizeof(uint32_t));
}