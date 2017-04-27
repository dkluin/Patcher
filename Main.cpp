#include "Main.h"
#include "VersionMgr/VersionMgr.h"
#include "HookingList/HookingList.h"
#include "RawHooks/RawHooks.h"

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
}