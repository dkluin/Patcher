#pragma once

#include "../Main.hpp"

namespace Memory
{
	class VersionMgr
	{
	public:
		// Initializes version manager
		static bool InitializeVersionMgr();

		// Shutdown version manager
		static bool ShutdownVersionMgr();
	};
}