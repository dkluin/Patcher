#pragma once

#include <string>

#define MAX_NUM_DETOURS 256

// Detours
class Detours
{
public:
	// Detour the function
	static void DetourFunction(std::string szModuleName, std::string szExportName, void* pDest, uint32_t& dwBackup, uint32_t iIndexInTable);

	// Gets the address
	static uint32_t GetExportAddress(std::string szModuleName, std::string szExportName);

	// Undo the detour and restore the value
	static void UndoDetour(std::string szModuleName, std::string szExportName, uint32_t dwBackup);

	// Detour table
	static uint32_t ms_pDetourFunctionPointers[MAX_NUM_DETOURS];
};