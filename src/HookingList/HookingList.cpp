#include "../Shared.hpp"
#include "HookingList.h"

// The list of hooking lists
std::vector<std::function<void()>>* HookingList::ms_vHookingLists;

HookingList::HookingList(std::function<void()> pHookingList)
{
	if (!ms_vHookingLists)
	{
		ms_vHookingLists = new std::vector<std::function<void()>>;
	}
	ms_vHookingLists->push_back(pHookingList);
}

void HookingList::RunAll()
{
	if (ms_vHookingLists)
	{
		for (auto it = ms_vHookingLists->cbegin(); it != ms_vHookingLists->cend(); it++)
		{
			(*it)();
		}
	}
}
