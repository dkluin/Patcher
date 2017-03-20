#include "HookingList.h"

namespace Patcher
{
	std::vector<std::function<void()>>* HookingList::function_list;


	HookingList::HookingList(std::function<void()> single_function)
	{
		if (!function_list)
		{
			function_list = new std::vector<std::function<void()>>;
		}
		function_list->push_back(single_function);
	}

	void HookingList::RunAll()
	{
		if (function_list)
		{
			for (auto function = function_list->cbegin(); function != function_list->cend(); function++)
			{
				(*function)();
			}

			// Destroy the entire list because it is no longer needed
			delete function_list;
		}
	}
}
