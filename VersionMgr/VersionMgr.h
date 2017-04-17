#pragma once

#include "../Main.h"

enum eVersions
{
	VERSION_GAME_UNKNOWN = 0,
	VERSION_GTA_III_1_0,
	VERSION_GTA_III_1_1,
	VERSION_GTA_III_CRACKED_STEAM,
	VERSION_GTA_III_ENCRYPTED_STEAM,
	VERSION_GTA_VC_1_0,
	VERSION_GTA_VC_1_1,
	VERSION_GTA_SA_1_0_US_CRACKED,
	VERSION_GTA_SA_1_0_US_COMPACT,
	VERSION_GTA_SA_1_0_DE,
	VERSION_GTA_SA_1_0_EU_CRACKED_1,
	VERSION_GTA_SA_1_0_EU_CRACKED_2,
	VERSION_GTA_SA_1_0_US_HOODLUM,
	VERSION_GTA_SA_1_0_EU_HOODLUM,
	VERSION_GTA_SA_1_1_US_CRACKED,
	VERSION_GTA_SA_1_1_EU_CRACKED,
	VERSION_GTA_SA_1_1_EU_DEVIANCE,
	VERSION_GTA_SA_3_0_CRACKED_STEAM,
	VERSION_GTA_SA_3_0_ENCRYPTED_STEAM
};

class VersionMgr
{
public:
	// Initializes version manager
	static bool InitializeVersionMgr(bool bEntryPointBasedVersionMgr); 

	// Initializes with a static entry point address - useful for PE loaders
	static bool InitializeVersionMgrStatic(uint32_t m_dwEntryPoint);

	// Shutdown version manager
	static bool ShutdownVersionMgr();

	// Is HOODLUM?
	static bool IsHoodlumUS();
	static bool IsHoodlumEU();

	// Is DEViANCE
	static bool IsDevianceEU();

	// Returns game version 
	static int GetGameVersion();

	// Convert address from EU to US
	static uint32_t ConvertAddressFromEUtoUS(uint32_t addr);
	static void ConvertAddressFromEUtoUS(Memory* addr);

	// Convert address from US to EU
	static uint32_t ConvertAddressFromUStoEU(uint32_t addr);
	static void ConvertAddressFromUStoEU(Memory* addr);

private:
	// Game version
	static int GameVersion;

	// Gets entry point
	static uint32_t GetEntryPoint();

	// Is file size based?
	static bool ms_bIsFileSizeBased;
};
