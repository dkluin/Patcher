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

		case 0x825890: // GTA SA 1.0 DE
			GameVersion = VERSION_GTA_SA_1_0_DE;
			break;

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
			if (IsDevianceEU())
			{
				GameVersion = VERSION_GTA_SA_1_1_EU_DEVIANCE;
			}
			else
			{
				GameVersion = VERSION_GTA_SA_1_1_EU_CRACKED;
			}
			break;

		case 0x85EC4A:  // GTA SA 3.0 (Cracked Steam Version)
			GameVersion = VERSION_GTA_SA_3_0_CRACKED_STEAM;
			break;

		case 0xD3C3DB:  // GTA SA 3.0 (Encrypted Steam Version)
			GameVersion = VERSION_GTA_SA_3_0_ENCRYPTED_STEAM;
			break;

		case 0x5C1E70:  // GTA III 1.0
			GameVersion = VERSION_GTA_III_1_0;
			break;

		case 0x5C2130:  // GTA III 1.1
			GameVersion = VERSION_GTA_III_1_1;
			break;

		case 0x5C6FD0:  // GTA III 1.1 (Cracked Steam Version)
			GameVersion = VERSION_GTA_III_CRACKED_STEAM;
			break;

		case 0x9912ED:  // GTA III 1.1 (Encrypted Steam Version)
			GameVersion = VERSION_GTA_III_ENCRYPTED_STEAM;
			break;

		case 0x667BF0:  // GTA VC 1.0
			GameVersion = VERSION_GTA_VC_1_0;
			break;

		case 0x667C40:  // GTA VC 1.1
			GameVersion = VERSION_GTA_VC_1_1;
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


	void VersionMgr::ConvertAddressFromEUtoUS(Memory* addr)
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

	void VersionMgr::ConvertAddressFromUStoEU(Memory* addr)
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
	}

	bool VersionMgr::IsDevianceEU()
	{
		return Memory::Memory(0x464780).Get<BYTE>(true) == 0xFF;
	}

}
