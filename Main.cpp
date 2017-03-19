#include "Main.hpp"

namespace Memory
{
	// Initialize the memory patching library
	bool Global::InitializePatcher()
	{
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
		Memory::Global::ShutdownPatcher();
	}
}