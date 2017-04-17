#pragma once

#include <Windows.h>
#include <cstdint>

#ifdef WIN32
class PluginPatcher
{
public:
	// Get plugin base address
	static HMODULE GetPluginModule(LPCSTR m_szPluginName) { return GetModuleHandle(m_szPluginName); }
	static HMODULE GetPluginModuleA(LPCSTR m_szPluginName) { return GetModuleHandleA(m_szPluginName); }
	static HMODULE GetPluginModuleW(LPWSTR m_szPluginName) { return GetModuleHandleW(m_szPluginName); }

	// Get plugin entry point
	static LPVOID GetPluginEntryPoint(LPCSTR m_szPluginName);
	static LPVOID GetPluginEntryPointA(LPCSTR m_szPluginName);
	static LPVOID GetPluginEntryPointW(LPWSTR m_szPluginName);

	// Plugin detours
	static uint32_t MakePluginJMP(HMODULE m_aModule, DWORD m_dwRelativeAddress, void* pDest, bool bVirtualProtect = true);
	static uint32_t MakePluginCALL(HMODULE m_aModule, DWORD m_dwRelativeAddress, void* pDest, bool bVirtualProtect = true);

	static void MakePluginRET(HMODULE m_aModule, DWORD m_dwRelativeAddress, bool bVirtualProtect = true);
};
#endif