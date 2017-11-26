#include "../Shared.hpp"
#include "Detours.h"
#include "../Injecting.h"

uint32_t Detours::ms_pDetourFunctionPointers[MAX_NUM_DETOURS];

// Detour the function
void Detours::DetourFunction(std::string szModuleName, std::string szExportName, void* pDest, uint32_t& dwBackup, uint32_t iIndexInTable)
{
	uint32_t pSource = reinterpret_cast<uint32_t>(GetProcAddress(GetModuleHandleA(szModuleName.c_str()), szExportName.c_str())) + 2;

	ms_pDetourFunctionPointers[iIndexInTable] = reinterpret_cast<uint32_t>(pDest);
	dwBackup = MemoryInjector::ReadMemory<uint32_t>(pSource);
	MemoryInjector::WriteMemory(pSource, ms_pDetourFunctionPointers);
}

// Undo the detour and restore the value
void Detours::UndoDetour(std::string szModuleName, std::string szExportName, const uint32_t dwBackup)
{
	uint32_t pSource = reinterpret_cast<uint32_t>(GetProcAddress(GetModuleHandleA(szModuleName.c_str()), szExportName.c_str())) + 2;

	MemoryInjector::WriteMemory<uint32_t>(pSource, dwBackup);
}

uint32_t Detours::GetExportAddress(std::string szModuleName, std::string szExportName)
{
	return reinterpret_cast<uint32_t>(GetProcAddress(GetModuleHandleA(szModuleName.c_str()), szExportName.c_str()));
}