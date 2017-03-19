#include "Main.hpp"
#include "Injecting.hpp"
#include "HookingList/HookingList.hpp"

namespace Memory
{
	// Initialize the memory patching library
	bool Global::InitializePatcher()
	{
		HookingList::RunAll();
		return true;
	}

	// Shutdown the memory patching library
	bool Global::ShutdownPatcher()
	{
		return true;
	}
}

void main()
{
	if (Memory::Global::InitializePatcher())
	{
		Memory::Memory wow(0x2345);

		wow % 1;

		Memory::Global::ShutdownPatcher();
	}
}