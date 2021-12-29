#pragma once

#include "../Main.h"

enum eVersions : int
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

class VersionAddress
{
public:
	uint32_t m_dwAddress;
	eVersions m_eVersion;

	VersionAddress(uint32_t dwAddress, eVersions eVersion = VERSION_GAME_UNKNOWN)
	{

	}
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

	// Accepts a range of addresses with a version identifier and returns the correct one based on the version obtained through InitializeVersionMgr
	static uint32_t GetAddressByVersion(std::initializer_list<VersionAddress> vVersionAddresses);

	// Gets entry point
	static uint32_t GetEntryPoint();

private:
	// Game version
	static int GameVersion;
};
