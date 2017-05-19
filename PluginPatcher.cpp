#include "Shared.hpp"
#include "PluginPatcher.h"
#include <Psapi.h>
#include "Injecting.h"

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

uint32_t PluginPatcher::MakePluginJMP(HMODULE m_aModule, uint32_t m_dwRelativeAddress, void* pDest, bool bVirtualProtect)
{
	return MemoryInjector::MakeJMP(reinterpret_cast<uint32_t>(m_aModule) + m_dwRelativeAddress, pDest, bVirtualProtect);
}

uint32_t PluginPatcher::MakePluginJMP(HMODULE m_aModule, Memory* m_dwRelativeAddress, void* pDest)
{
	Memory m_Module(m_dwRelativeAddress);
	m_Module.ChangeAddress(reinterpret_cast<uint32_t>(m_aModule) + m_dwRelativeAddress->GetAddress());
	return MemoryInjector::MakeJMP(&m_Module, pDest);
}

uint32_t PluginPatcher::MakePluginJMP(HMODULE m_aModule, uint32_t m_dwRelativeAddress, uint32_t m_pDest, bool bProtect)
{
	return MemoryInjector::MakeJMP(reinterpret_cast<uint32_t>(m_aModule) + m_dwRelativeAddress, m_pDest, bProtect);
}

uint32_t PluginPatcher::MakePluginJMP(HMODULE m_aModule, Memory* m_dwRelativeAddress, uint32_t m_pDest)
{
	Memory m_Module(m_dwRelativeAddress);
	m_Module.ChangeAddress(reinterpret_cast<uint32_t>(m_aModule) + m_dwRelativeAddress->GetAddress());
	return MemoryInjector::MakeJMP(&m_Module, m_pDest);
}

uint32_t PluginPatcher::MakePluginCALL(HMODULE m_aModule, uint32_t m_dwRelativeAddress, void* pDest, bool bVirtualProtect)
{
	return MemoryInjector::MakeCALL(reinterpret_cast<uint32_t>(m_aModule) + m_dwRelativeAddress, pDest, bVirtualProtect);
}

uint32_t PluginPatcher::MakePluginCALL(HMODULE m_aModule, Memory* m_dwRelativeAddress, void* pDest)
{
	Memory m_Module(m_dwRelativeAddress);
	m_Module.ChangeAddress(reinterpret_cast<uint32_t>(m_aModule) + m_dwRelativeAddress->GetAddress());
	return MemoryInjector::MakeCALL(&m_Module, pDest);
}

uint32_t PluginPatcher::MakePluginCALL(HMODULE m_aModule, uint32_t m_dwRelativeAddress, uint32_t m_pDest, bool bProtect)
{
	return MemoryInjector::MakeCALL(reinterpret_cast<uint32_t>(m_aModule) + m_dwRelativeAddress, m_pDest, bProtect);
}

uint32_t PluginPatcher::MakePluginCALL(HMODULE m_aModule, Memory* m_dwRelativeAddress, uint32_t m_pDest)
{
	Memory m_Module(m_dwRelativeAddress);
	m_Module.ChangeAddress(reinterpret_cast<uint32_t>(m_aModule) + m_dwRelativeAddress->GetAddress());
	return MemoryInjector::MakeCALL(&m_Module, m_pDest);
}

void PluginPatcher::MakePluginRET(HMODULE m_aModule, uint32_t m_dwRelativeAddress, bool bVirtualProtect)
{
	MemoryInjector::MakeRET(reinterpret_cast<uint32_t>(m_aModule) + m_dwRelativeAddress, bVirtualProtect);
}

void PluginPatcher::MakePluginRET(HMODULE m_aModule, Memory* m_dwRelativeAddress)
{
	Memory m_Module(m_dwRelativeAddress);
	m_Module.ChangeAddress(reinterpret_cast<uint32_t>(m_aModule) + m_dwRelativeAddress->GetAddress());
	MemoryInjector::MakeRET(&m_Module);
}