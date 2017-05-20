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

	// Raw hooks buffer, dont touch
	static uint8_t* ms_pTheRawHooks;

	// Current position in buffer
	static uint32_t ms_nGlobalPos;

	static std::vector<RawHookVariable*> m_vVariables;
};