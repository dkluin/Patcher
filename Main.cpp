#include "Main.h"
#include "VersionMgr/VersionMgr.h"
#include "HookingList/HookingList.h"

namespace Patcher
{
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
}