#pragma once

#include <vector>
#include <functional>

class HookingList
{
private:
	static std::vector<std::function<void()>>* function_list;

public:
	// Run it all!
	static void RunAll();

	HookingList(std::function<void()> single_function);
};