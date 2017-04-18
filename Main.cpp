#include "Main.h"
#include "VersionMgr/VersionMgr.h"
#include "HookingList/HookingList.h"

bool Main::Initialize(bool bEntryPointBasedVersionMgr)
{
	if (bEntryPointBasedVersionMgr)
	{
		if (VersionMgr::InitializeVersionMgr(bEntryPointBasedVersionMgr))
		{
			HookingList::RunAll();
			return true;
		}
		else
		{
			return false;
		}
	}
}