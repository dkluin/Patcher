#include "VersionMgr.h"
#include "../Main.h"
#include <Psapi.h>

namespace Patcher
{
	// Game version
	int VersionMgr::GameVersion = VERSION_GAME_UNKNOWN;

	// Initializes version manager
	bool VersionMgr::InitializeVersionMgr()
	{
		// Credits: https://github.com/thelink2012/injector/blob/master/include/injector/injector.hpp for entry point addresses
		switch (GetEntryPoint())
		{
		case 0x82457C: // GTA SA 1.0 US Cracked
			if (IsHoodlumUS())
			{
				GameVersion = VERSION_GTA_SA_1_0_US_HOODLUM;
				break;
			}
			else
			{
				GameVersion = VERSION_GTA_SA_1_0_US_CRACKED;
				break;
			}
		case 0x824570: // GTA SA 1.0 US Compact
			if (IsHoodlumUS())
			{
				GameVersion = VERSION_GTA_SA_1_0_US_HOODLUM;
				break;
			}
			else
			{
				GameVersion = VERSION_GTA_SA_1_0_US_COMPACT;
				break;
			}
		case 0x8245BC:  // GTA SA 1.0 EU Cracked (??????)
			if (IsHoodlumEU())
			{
				GameVersion = VERSION_GTA_SA_1_0_EU_HOODLUM;
				break;
			}
			else
			{
				GameVersion = VERSION_GTA_SA_1_0_EU_CRACKED_1;
				break;
			}
		case 0x8245B0:  // GTA SA 1.0 EU Cracked
			if (IsHoodlumEU())
			{
				GameVersion = VERSION_GTA_SA_1_0_EU_HOODLUM;
				break;
			}
			else
			{
				GameVersion = VERSION_GTA_SA_1_0_EU_CRACKED_2;
				break;
			}
		case 0x8252FC:  // GTA SA 1.1 US Cracked
			GameVersion = VERSION_GTA_SA_1_1_US_CRACKED;
			break;
		case 0x82533C:  // GTA SA 1.1 EU Cracked
			GameVersion = VERSION_GTA_SA_1_1_EU_CRACKED;
			break;
		case 0x85EC4A:  // GTA SA 3.0 (Cracked Steam Version)
			GameVersion = VERSION_GTA_SA_3_0_CRACKED_STEAM;
			break;
		case 0xD3C3DB:  // GTA SA 3.0 (Encrypted Steam Version)
			GameVersion = VERSION_GTA_SA_3_0_ENCRYPTED_STEAM;
			break;

		default:
			return false;
		}
		return true;
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

	int VersionMgr::GetGameVersion()
	{
		return GameVersion;
	}

	uint32_t VersionMgr::ConvertAddressFromEUtoUS(uint32_t addr)
	{

	}


	Memory* VersionMgr::ConvertAddressFromEUtoUS(Memory* addr)
	{

	}

	uint32_t VersionMgr::ConvertAddressFromUStoEU(uint32_t addr)
	{
		if (addr > 0x7466D0)
		{
			if (addr < 0x7BA940)
			{
				addr += 0x50;
			}
			else
			{
				addr += 0x40;
			}
		}
		return addr;
	}

	static Memory* ConvertAddressFromUStoEU(Memory* addr)
	{
		if (addr->GetAddress() > 0x7466D0)
		{
			if (addr->GetAddress() < 0x7BA940)
			{
				addr->ChangeAddress(addr->GetAddress() + 0x50);
			}
			else
			{
				addr->ChangeAddress(addr->GetAddress() + 0x40);
			}
		}
		return addr;
	}

}
