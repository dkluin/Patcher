#pragma once
struct PatcherInfo
{
	// Standard
	uint32_t ms_NumberOfInjectedFunctions;
	uint32_t ms_NumberOfMemoryPatches;
	uint32_t ms_TimesDataWasNOPped;
	uint32_t ms_MemoryCopied;
	uint32_t ms_MemorySet;

	// Raw functions
	uint32_t ms_NumberOfRawMemorySections;
	uint32_t ms_NumberOfRawMemorySubSections;
	uint32_t ms_NumberOfRawMemorySectionJMPs;

	// Patcher list
	uint32_t ms_NumberOfPatcherLists;
	uint32_t ms_NumberOfPatchesAppliedFromPatcherLists;

	// Levels
	uint32_t ms_HighestPatcherLevel;
	uint32_t ms_NumberOfLevelsWithStepByStepPatcherEnabled;
	uint32_t ms_NumberOfLevelsWithWithDebugMode;

	// Function calling
	uint32_t ms_CalledFunctions;

	// Total
	uint32_t ms_TotalNumberOfMemoryChanges;

	// Game version - not really needed but still present
	// some already done future-proof functions are done too!
	uint8_t ms_PatcherGameVersion;

	// Patcher stack
	bool bEnablePatcherStack;
	bool bPatcherInitialized;
};