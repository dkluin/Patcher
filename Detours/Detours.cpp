#include "../Shared.hpp"
#include "Detours.h"
#include "../Injecting.h"

// Detour the function
void Detours::DetourFunction(HMODULE hModule, std::string szExportName, void* pDest, uint64_t& qwBackup)
{
	uint32_t pSource = reinterpret_cast<uint32_t>(GetProcAddress(hModule, szExportName.c_str()));

	qwBackup = MemoryInjector::ReadMemory<uint64_t>(pSource);
	MemoryInjector::MakeJMP(pSource, pDest);
}

void Detours::DetourFunction(std::string szModuleName, std::string szExportName, void* pDest, uint64_t& qwBackup)
{
	uint32_t pSource = reinterpret_cast<uint32_t>(GetProcAddress(GetModuleHandleA(szModuleName.c_str()), szExportName.c_str()));

	qwBackup = MemoryInjector::ReadMemory<uint64_t>(pSource);
	MemoryInjector::MakeJMP(pSource, pDest);
}

// Undo the detour and restore the value
void Detours::UndoDetour(HMODULE hModule, std::string szExportName, const uint64_t qwBackup)
{
	uint32_t pSource = reinterpret_cast<uint32_t>(GetProcAddress(hModule, szExportName.c_str()));

	MemoryInjector::WriteMemory<uint64_t>(pSource, qwBackup);
}

void Detours::UndoDetour(std::string szModuleName, std::string szExportName, const uint64_t qwBackup)
{
	uint32_t pSource = reinterpret_cast<uint32_t>(GetProcAddress(GetModuleHandleA(szModuleName.c_str()), szExportName.c_str()));

	MemoryInjector::WriteMemory<uint64_t>(pSource, qwBackup);
}