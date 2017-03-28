#include "PluginPatcher.h"
#include <Psapi.h>

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
#endif