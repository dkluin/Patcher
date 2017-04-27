#pragma once

#include <string>
#include "../Memory.h"

class Detours
{
public:
	// Makes a detour JMP my hooking an exported library function (which has to be injected into the executable)
	static void MakeDetourJMP(std::string m_szExportedModuleName, std::string m_szExportedFunctionName, void* m_pFunction);
};