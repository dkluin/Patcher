#pragma once

#include "TheRawHooks.h"

uint8_t* TheRawHooks::ms_pTheRawHooks;
uint32_t TheRawHooks::ms_nGlobalPos;
std::vector<RawHookVariable*> TheRawHooks::m_vVariables;

bool TheRawHooks::Initialize()
{
	ms_pTheRawHooks = new uint8_t[THERAWHOOKS_SPACE];
	if (ms_pTheRawHooks)
	{
		ms_nGlobalPos = 0;
		return true;
	}
	else
	{
		return false;
	}
}

bool TheRawHooks::Shutdown()
{
	if (ms_pTheRawHooks)
	{
		free(ms_pTheRawHooks);
	}
	return true;
}


void TheRawHooks::StaticRawHook(uint32_t m_dwJumpFrom, uint32_t m_dwJumpTo, const void* m_nData, size_t m_iSize)
{
	RawHook m_Hook(m_dwJumpFrom, m_dwJumpTo);
	m_Hook.Start();
	m_Hook.Write(m_nData, m_iSize);
	m_Hook.Finish();
}
