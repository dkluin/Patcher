#pragma once
#include <stdint.h>
#include <vector>
#include "RawHookVariable.h"
#include "RawHook.h"
#include "../Memory.h"

#define THERAWHOOKS_SPACE 0xFFFF

class TheRawHooks
{
public:
	static bool Initialize();
	static bool Shutdown();

	static uint8_t* ms_pTheRawHooks;
	static uint32_t ms_nGlobalPos;

	static std::vector<RawHookVariable*> m_vVariables;

	// Static raw hook, a wrapper around RawHook which works slightly different than RawHook itself.
	// Accepts variable names.
	static void StaticRawHook(uint32_t dwJumpFrom, std::string szBytes, uint32_t dwJumpTo);
	static void StaticRawHook(Memory* pJumpFrom, std::string szBytes, Memory* pJumpTo);

private:
	// Replace all occurences of szFrom with szTo in string szTargetStr
	static void ReplaceAllInString(std::string& szTargetStr, const std::string& szFrom, const std::string& szTo);
};