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

	// Wrappers around RawHookVariable constructor for laziness sake
	static inline RawHookVariable* CreateVariable(std::string szVariableName, uint8_t bValue)
	{
		return new RawHookVariable(szVariableName, bValue);
	}

	static inline RawHookVariable* CreateVariable(const char* szVariableName, uint8_t bValue)
	{
		return new RawHookVariable(szVariableName, bValue);
	}

	static inline RawHookVariable* CreateVariable(std::string szVariableName, uint16_t wValue)
	{
		return new RawHookVariable(szVariableName, wValue);
	}

	static inline RawHookVariable* CreateVariable(const char* szVariableName, uint16_t wValue)
	{
		return new RawHookVariable(szVariableName, wValue);
	}

	static inline RawHookVariable* CreateVariable(std::string szVariableName, uint32_t dwValue)
	{
		return new RawHookVariable(szVariableName, dwValue);
	}

	static inline RawHookVariable* CreateVariable(const char* szVariableName, uint32_t dwValue)
	{
		return new RawHookVariable(szVariableName, dwValue);
	}

	static inline RawHookVariable* CreateVariable(std::string szVariableName, float fValue)
	{
		return new RawHookVariable(szVariableName, fValue);
	}

	static inline RawHookVariable* CreateVariable(const char* szVariableName, float fValue)
	{
		return new RawHookVariable(szVariableName, fValue);
	}

	// Wrapper around RawHookVariables destructor
	static inline void DeleteVariable(RawHookVariable* pVariable)
	{
		delete pVariable;
	}

private:
	// Replace all occurences of szFrom with szTo in string szTargetStr
	static void ReplaceAllInString(std::string& szTargetStr, const std::string& szFrom, const std::string& szTo);
};