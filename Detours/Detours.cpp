#include "Detours.h"
#include "../Injecting.h"

// TODO: use Memory class for backup?
void Detours::MakeDetourJMP(std::string m_szExportedModuleName, std::string m_szExportedFunctionName, void* m_pFunction)
{
	void* m_Function = GetProcAddress(GetModuleHandle(m_szExportedModuleName.c_str()), m_szExportedFunctionName.c_str());
	MemoryInjector::MakeJMP((uint32_t)m_Function, m_pFunction, true);
}

void Detours::UndoDetourJMP()
{

}