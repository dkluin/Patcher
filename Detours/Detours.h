#pragma once

#include <string>

// Detours
class Detours
{
public:
	// Detour the function
	static void DetourFunction(HMODULE hModule, std::string szExportName, void* pDest, uint64_t& qwBackup);
	static void DetourFunction(std::string szModuleName, std::string szExportName, void* pDest, uint64_t& qwBackup);

	// Undo the detour and restore the value
	static void UndoDetour(HMODULE hModule, std::string szExportName, const uint64_t qwBackup);
	static void UndoDetour(std::string szModuleName, std::string szExportName, const uint64_t qwBackup);
};