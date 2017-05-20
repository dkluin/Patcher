
/*
	TheRawHooks.h

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