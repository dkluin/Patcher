#include "Main.h"
#include "VersionMgr/VersionMgr.h"
#include "HookingList/HookingList.h"

bool Main::Initialize()
{
	if (VersionMgr::InitializeVersionMgr())
	{
		HookingList::RunAll();
		return true;
	}
	else
	{
		return false;
	}
}