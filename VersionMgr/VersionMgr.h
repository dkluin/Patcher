#pragma once

#include "../Main.h"

namespace Patcher
{
	enum eVersions
	{
		VERSION_GAME_UNKNOWN = 0,
		VERSION_GTA_SA_1_0_US_CRACKED,
		VERSION_GTA_SA_1_0_US_COMPACT,
		VERSION_GTA_SA_1_0_EU_CRACKED_1,
		VERSION_GTA_SA_1_0_EU_CRACKED_2,
		VERSION_GTA_SA_1_0_US_HOODLUM,
		VERSION_GTA_SA_1_0_EU_HOODLUM,
		VERSION_GTA_SA_1_1_US_CRACKED,
		VERSION_GTA_SA_1_1_EU_CRACKED,
		VERSION_GTA_SA_3_0_CRACKED_STEAM,
		VERSION_GTA_SA_3_0_ENCRYPTED_STEAM
	};

	class VersionMgr
	{
	public:
		// Initializes version manager
		static bool InitializeVersionMgr();

		// Shutdown version manager
		static bool ShutdownVersionMgr();

		// Is HOODLUM?
		static bool IsHoodlumUS();
		static bool IsHoodlumEU();

		// Returns game version 
		static int GetGameVersion();

		// Convert address from EU to US
		static uint32_t ConvertAddressFromEUtoUS(uint32_t addr);
		static Memory* ConvertAddressFromEUtoUS(Memory* addr);

	private:
		// Game version
		static int GameVersion;

		// Gets entry point
		static uint32_t GetEntryPoint();
	};
}
