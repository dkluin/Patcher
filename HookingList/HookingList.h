#pragma once

#include <vector>
#include <functional>

class HookingList
{
private:
	static std::vector<std::function<void()>>* ms_vHookingLists;

public:
	// Run it all!
	static void RunAll();

	HookingList(std::function<void()> pHookingList);
};