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
			case 0x82457C: // GTA SA 1.0 US Cracked
			case 0x824570: // GTA SA 1.0 US Compact
				return IsHoodlumUS();
			case 0x8245BC:  // GTA SA 1.0 EU Cracked (??????)
			case 0x8245B0:  // GTA SA 1.0 EU Cracked
				return IsHoodlumEU();
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

	bool VersionMgr::IsHoodlumUS()
	{
		return Memory::Memory(0x406A20).Get<BYTE>(true) == 0xE9;
	}

	bool VersionMgr::IsHoodlumEU()
	{
		return Memory::Memory(0x406A20).Get<BYTE>(true) == 0xE9;
	}
}