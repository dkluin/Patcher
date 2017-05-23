#pragma once

#include <Windows.h>
#include <cstdint>
#include <string>
#include "Memory.h"

/*
	TODO:
	- Rename PluginPatcher to ModulePatcher, even though UG uses it to patch plugins in Underground_Core.asi
	- Restorable patching in the future
*/

class PluginPatcher
{
public:
	// Get plugin base address
	static inline HMODULE GetPluginModule(LPCSTR m_szPluginName) { return GetModuleHandle(m_szPluginName); }
	static inline HMODULE GetPluginModuleA(LPCSTR m_szPluginName) { return GetModuleHandleA(m_szPluginName); }
	static inline HMODULE GetPluginModuleW(LPWSTR m_szPluginName) { return GetModuleHandleW(m_szPluginName); }
	static inline HMODULE GetPluginModule(std::string m_szPluginName) { return GetModuleHandle(m_szPluginName.c_str()); }
	static inline HMODULE GetPluginModuleA(std::string m_szPluginName) { return GetModuleHandleA(m_szPluginName.c_str()); }
	static inline HMODULE GetPluginModuleW(std::wstring m_szPluginName) { return GetModuleHandleW(m_szPluginName.c_str()); }

	// Get plugin entry point
	static LPVOID GetPluginEntryPoint(LPCSTR m_szPluginName);
	static LPVOID GetPluginEntryPointA(LPCSTR m_szPluginName);
	static LPVOID GetPluginEntryPointW(LPWSTR m_szPluginName);

	// Inlined alternatives for those who whish to use std::string
	static inline LPVOID GetPluginEntryPoint(std::string m_szPluginName)
	{
		return GetPluginEntryPoint(m_szPluginName.c_str());
	}

	static inline LPVOID GetPluginEntryPointA(std::string m_szPluginName)
	{
		return GetPluginEntryPointA(m_szPluginName.c_str());
	}

	static inline LPVOID GetPluginEntryPointW(std::wstring m_szPluginName)
	{
		return GetPluginEntryPointW(m_szPluginName.c_str());
	}

	// Wrapper around GetProcAddress for laziness sake
	static inline uint32_t GetPluginProcAddress(HMODULE hModule, std::string szExported) { return reinterpret_cast<uint32_t>(GetProcAddress(hModule, szExported.c_str())); }

	// Makes a JMP in a loaded module
	static void MakePluginJMP(HMODULE m_aModule, uint32_t m_dwRelativeAddress, void* pDest, bool bVirtualProtect = true);
	static void MakePluginJMP(HMODULE m_aModule, Memory* m_dwRelativeAddress, void* pDest);
	static void MakePluginJMP(HMODULE m_aModule, uint32_t m_dwRelativeAddress, uint32_t m_pDest, bool bProtect = true);
	static void MakePluginJMP(HMODULE m_aModule, Memory* m_dwRelativeAddress, uint32_t m_pDest);

	// Makes a CALL in a loaded module
	static void MakePluginCALL(HMODULE m_aModule, uint32_t m_dwRelativeAddress, void* pDest, bool bVirtualProtect = true);
	static void MakePluginCALL(HMODULE m_aModule, Memory* m_dwRelativeAddress, void* pDest);
	static void MakePluginCALL(HMODULE m_aModule, uint32_t m_dwRelativeAddress, uint32_t m_pDest, bool bProtect = true);
	static void MakePluginCALL(HMODULE m_aModule, Memory* m_dwRelativeAddress, uint32_t m_pDest);

	// Make a plugin RET
	static void MakePluginRET(HMODULE m_aModule, uint32_t m_dwRelativeAddress, bool bVirtualProtect = true);
	static void MakePluginRET(HMODULE m_aModule, Memory* m_dwRelativeAddress);
};
