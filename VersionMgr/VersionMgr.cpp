#include "VersionMgr.hpp"
#include "../Main.hpp"
#include <Psapi.h>


namespace Memory
{
	// Initializes version manager
	bool VersionMgr::InitializeVersionMgr()
	{
		if (GetEntryPoint())
		{
			switch (GetEntryPoint())
			{
			case 0x82457C:
			case 0x824570:
				return true;
			}

			return true;
		}
		return false;
	}

	// Shutdown version manager
	bool VersionMgr::ShutdownVersionMgr()
	{
		return true;
	}

	uint32_t VersionMgr::GetEntryPoint()
	{
		MODULEINFO info;
		GetModuleInformation(GetCurrentProcess(), GetModuleHandle(NULL), &info, sizeof(MODULEINFO));

		return (uint32_t)info.EntryPoint;
	}

	bool VersionMgr::IsHoodlum()
	{
		return Memory::Memory(0x406A20).Get<BYTE>(true) == 0xE9;
	}
}