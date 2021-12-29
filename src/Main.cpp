#include "Shared.hpp"
#include "Main.h"
#include "VersionMgr/VersionMgr.h"
#include "HookingList/HookingList.h"
#include "RawHooks/TheRawHooks.h"

bool Main::Initialize(bool bEntryPointBasedVersionMgr)
{
	if (bEntryPointBasedVersionMgr)
	{
		if (VersionMgr::InitializeVersionMgr(bEntryPointBasedVersionMgr))
		{
			TheRawHooks::Initialize();
			HookingList::RunAll();
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false; // aaaaaaaaaaaaa
	}
}

void Main::Shutdown()
{
	TheRawHooks::Shutdown();
}