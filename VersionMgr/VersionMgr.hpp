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

		// Is HOODLUM?
		static bool IsHoodlumUS();
		static bool IsHoodlumEU();

	private:
		// Game version
		static int GameVersion;

		// Gets entry point
		static uint32_t GetEntryPoint();
	};
}