#pragma once
#include <stdint.h>
#include <vector>
#include "RawHookVariable.h"
#include "RawHook.h"

#define THERAWHOOKS_SPACE 0xFFFF

class TheRawHooks
{
public:
	static bool Initialize();
	static bool Shutdown();

	static void StaticRawHook(uint32_t m_dwJumpFrom, uint32_t m_dwJumpTo, const void* m_nData, size_t m_iSize);

	static uint8_t* ms_pTheRawHooks;
	static uint32_t ms_nGlobalPos;

	static std::vector<RawHookVariable*> m_vVariables;
};