#include "PluginPatcher.h"
#include <Psapi.h>
#include "Injecting.h"

#ifdef WIN32
LPVOID PluginPatcher::GetPluginEntryPoint(LPCSTR m_szPluginName)
{
	MODULEINFO info;
	GetModuleInformation(GetCurrentProcess(), GetModuleHandle(m_szPluginName), &info, sizeof(MODULEINFO));
	return info.EntryPoint;
}

LPVOID PluginPatcher::GetPluginEntryPointA(LPCSTR m_szPluginName)
{
	MODULEINFO info;
	GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(m_szPluginName), &info, sizeof(MODULEINFO));
	return info.EntryPoint;
}

LPVOID PluginPatcher::GetPluginEntryPointW(LPWSTR m_szPluginName)
{
	MODULEINFO info;
	GetModuleInformation(GetCurrentProcess(), GetModuleHandleW(m_szPluginName), &info, sizeof(MODULEINFO));
	return info.EntryPoint;
}

uint32_t PluginPatcher::MakePluginJMP(HMODULE m_aModule, DWORD m_dwRelativeAddress, void* pDest, bool bVirtualProtect)
{
	return MemoryInjector::MakeJMP((uint32_t)m_aModule + m_dwRelativeAddress, pDest, bVirtualProtect);
}

uint32_t PluginPatcher::MakePluginCALL(HMODULE m_aModule, DWORD m_dwRelativeAddress, void* pDest, bool bVirtualProtect)
{
	return MemoryInjector::MakeCALL((uint32_t)m_aModule + m_dwRelativeAddress, pDest, bVirtualProtect);
}

uint32_t PluginPatcher::MakePluginRET(HMODULE m_aModule, DWORD m_dwRelativeAddress, size_t m_iSize)
{
	return NULL; // Still need to do it
}
#endif