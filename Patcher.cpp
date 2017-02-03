#include "../../Shared.hpp"
#include "Patcher.h"

PatcherInfo Patcher::ms_PatcherData;

// Patcher level info
PatcherLevelInfo Patcher::PatcherLevel::PatcherLevelInfoArray[128];

// Current level
int Patcher::PatcherLevel::CurrentPatcherLevel;

// Current level INFO
PatcherLevelInfo Patcher::PatcherLevel::Info;

bool Patcher::Initialize()
{
	// Set standard patcher level 
	PatcherLevel::CurrentPatcherLevel = 64;

	// Clear PatcherData
	ms_PatcherData.bEnablePatcherStack = false;

	ms_PatcherData.ms_HighestPatcherLevel = 0;
	ms_PatcherData.ms_NumberOfInjectedFunctions = 0;
	ms_PatcherData.ms_NumberOfLevelsWithStepByStepPatcherEnabled = 0;
	ms_PatcherData.ms_NumberOfLevelsWithWithDebugMode = 0;
	ms_PatcherData.ms_NumberOfMemoryPatches = 0;
	ms_PatcherData.ms_NumberOfPatcherLists = 0;
	ms_PatcherData.ms_NumberOfPatchesAppliedFromPatcherLists = 0;
	ms_PatcherData.ms_NumberOfRawMemorySectionJMPs = 0;
	ms_PatcherData.ms_NumberOfRawMemorySections = 0;
	ms_PatcherData.ms_NumberOfRawMemorySubSections = 0;
	ms_PatcherData.ms_PatcherGameVersion = GAME_VERSION_GTASA_US_1_0_HOODLUM;
	ms_PatcherData.ms_TimesDataWasNOPped = 0;
	ms_PatcherData.ms_CalledFunctions = 0;
	ms_PatcherData.ms_MemoryCopied = 0;
	ms_PatcherData.ms_MemorySet = 0;
	ms_PatcherData.ms_TotalNumberOfMemoryChanges = 0;

	ms_PatcherData.bPatcherInitialized = true;

	// Apply all patcher lists
	PatcherList::ApplyAllPatcherLists();

	return PluginPatcher::ValidateFiles();
}

// Write RET
void Patcher::WriteRET(uintptr_t addr)
{
	PatchOnAddress<BYTE>(addr, 0xC3);
}

// NOPs addresses - works
void Patcher::NOPData(uintptr_t addr, int size)
{
	if (MemorySection::GetMemorySectionForThisAddress(addr) == MEMORY_SEGMENT_STANDARD ||
		MemorySection::GetMemorySectionForThisAddress(addr) == MEMORY_SEGMENT_WRITEONLY)
	{
		DWORD dwProtect[2];
		VirtualProtect((PVOID)addr, size, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
		memset((PVOID)addr, 0x90, size);
		VirtualProtect((PVOID)addr, size, dwProtect[0], &dwProtect[1]);

		ms_PatcherData.ms_TotalNumberOfMemoryChanges++;
		ms_PatcherData.ms_TimesDataWasNOPped++;
	}
}

void Patcher::InjectFunctionPatchOnMultipleAddresses(void* dest_addr, x86_func_type type, std::initializer_list<uintptr_t> addr2)
{
	for (auto addr : addr2)
	{
		if (MemorySection::GetMemorySectionForThisAddress(addr) == MEMORY_SEGMENT_STANDARD ||
			MemorySection::GetMemorySectionForThisAddress(addr) == MEMORY_SEGMENT_WRITEONLY)
		{
			unsigned __int8 jmp_data[5];
			uintptr_t movement = (uintptr_t)dest_addr - addr - 5;

			switch (type)
			{
			case X86_FUNC_TYPE_DEFAULT:
			case X86_FUNC_TYPE_JMP:
				jmp_data[0] = 0xE9;
				break;
			case X86_FUNC_TYPE_CALL:
				jmp_data[0] = 0xE8;
				break;

			default:
				jmp_data[0] = 0xE9;
				break;
			}

			*(DWORD*)(jmp_data + 1) = movement;

			WriteDataToMemory((void*)addr, jmp_data, sizeof(jmp_data));

			ms_PatcherData.ms_NumberOfInjectedFunctions++;
			ms_PatcherData.ms_TotalNumberOfMemoryChanges++;
		}
	}
}

uintptr_t Patcher::CalculateJMPaddress(uintptr_t addr)
{
	uintptr_t offset = ReadMemory<uintptr_t>(addr + 1);
	return offset + addr + 5;
}

void Patcher::InjectFunctionPatchOnMultipleAddresses(uintptr_t dest_addr, x86_func_type type, std::initializer_list<uintptr_t> addr2)
{
	for (auto addr : addr2)
	{
		if (MemorySection::GetMemorySectionForThisAddress(addr) == MEMORY_SEGMENT_STANDARD ||
			MemorySection::GetMemorySectionForThisAddress(addr) == MEMORY_SEGMENT_WRITEONLY)
		{
			unsigned __int8 jmp_data[5];
			uintptr_t movement = (uintptr_t)dest_addr - addr - 5;

			switch (type)
			{
			case X86_FUNC_TYPE_DEFAULT:
			case X86_FUNC_TYPE_JMP:
				jmp_data[0] = 0xE9;
				break;
			case X86_FUNC_TYPE_CALL:
				jmp_data[0] = 0xE8;
				break;

			default:
				jmp_data[0] = 0xE9;
				break;
			}

			*(DWORD*)(jmp_data + 1) = movement;

			WriteDataToMemory((void*)addr, jmp_data, sizeof(jmp_data));

			ms_PatcherData.ms_NumberOfInjectedFunctions++;
			ms_PatcherData.ms_TotalNumberOfMemoryChanges++;
		}
	}
}

///////// Inherited from hax library by iFarbod
// MemCpy with unprotection of address
void Patcher::MemCpy(uintptr_t addr, const void* dest, size_t size)
{
	DWORD dwProtect[2];
	VirtualProtect((PVOID)addr, size, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
	memcpy((PVOID)addr, dest, size);
	VirtualProtect((PVOID)addr, size, dwProtect[0], &dwProtect[1]);
	ms_PatcherData.ms_MemoryCopied++;
}

// MemSet with unprotection of address
void Patcher::MemSet(uintptr_t addr, int32_t value, size_t size)
{
	DWORD dwProtect[2];
	VirtualProtect((PVOID)addr, size, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
	memset((PVOID)addr, value, size);
	VirtualProtect((PVOID)addr, size, dwProtect[0], &dwProtect[1]);
	ms_PatcherData.ms_MemorySet++;
}

// INTO THEJMPPATCH!!!
void Patcher::InjectJMPpatch(uintptr_t src, void* dest, x86_jmp_type type)
{
	if (MemorySection::GetMemorySectionForThisAddress(src) == MEMORY_SEGMENT_STANDARD ||
		MemorySection::GetMemorySectionForThisAddress(src) == MEMORY_SEGMENT_WRITEONLY)
	{
		unsigned __int8 jmp_data[6];
		uintptr_t movement = (uintptr_t)dest - src - 6;
		jmp_data[0] = type;

		*(DWORD*)(jmp_data + 2) = movement;
		PatchMemData(src, jmp_data, sizeof(jmp_data));
		ms_PatcherData.ms_NumberOfInjectedFunctions++;
	}
}

void Patcher::InjectJMPpatch(uintptr_t src, uintptr_t dest, x86_jmp_type type)
{
	InjectJMPpatch(src, (void*)dest, type);
}

// Inject any type of function patch - jmp and call only - works
void Patcher::InjectFunctionPatch(uintptr_t addr, void* function_name, x86_func_type type)
{
	if (MemorySection::GetMemorySectionForThisAddress(addr) == MEMORY_SEGMENT_STANDARD ||
		MemorySection::GetMemorySectionForThisAddress(addr) == MEMORY_SEGMENT_WRITEONLY)
	{
		unsigned __int8 jmp_data[5];
		uintptr_t movement = (uintptr_t)function_name - addr - 5;

		switch (type)
		{
		case X86_FUNC_TYPE_DEFAULT:
		case X86_FUNC_TYPE_JMP:
			jmp_data[0] = 0xE9;
			break;
		case X86_FUNC_TYPE_CALL:
			jmp_data[0] = 0xE8;
			break;

		default:
			jmp_data[0] = 0xE9;
			break;
		}

		*(DWORD*)(jmp_data + 1) = movement;
		PatchMemData(addr, jmp_data, sizeof(jmp_data));
		ms_PatcherData.ms_NumberOfInjectedFunctions++;
	}
}

// Alternate variant, specifies address
void Patcher::InjectFunctionPatch(uintptr_t addr, uintptr_t redirect_addr, x86_func_type type)
{
	InjectFunctionPatch(addr, (void*)redirect_addr, type);
}

// Patches memory data and increases total number of memory changes counter - works
void Patcher::PatchMemData(uintptr_t addr, const void* data, int size)
{
	WriteDataToMemory((void*)addr, data, size);
	ms_PatcherData.ms_TotalNumberOfMemoryChanges++;
}

// works
void Patcher::WriteDataToMemory(void* addr, const void* data, int size)
{
	DWORD dwProtect[2];
	VirtualProtect((PVOID)addr, size, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
	memcpy((PVOID)addr, data, size);
	VirtualProtect((PVOID)addr, size, dwProtect[0], &dwProtect[1]);
}

// Fill memory with zeroes, zero size is 4 bytes! Recalculate where needed!
void Patcher::FillMemoryWithZeroes(uintptr_t addr, size_t size)
{
	SetMemoryToValue((void*)addr, 0, size);
}

void Patcher::FillMemoryWithZeroes(void* addr, size_t size)
{
	SetMemoryToValue(addr, 0, size);
}


//////////////////////////// END OF STANDARD CODE

//////////////////////////// RAW MEMORY MANAGER

RawMemorySection Patcher::RawMemoryMgr::AllocateNewRawDataSection(size_t size)
{
	// First, create new raw data section.
	RawMemorySection result;

	// Initialize this section
	result.SectionPtr = new BYTE[size];
	result.CurrentPosition = 0x0;
	result.RawDataSectionSize = size;

	DWORD dwProtect;
	VirtualProtect(result.SectionPtr, size, PAGE_EXECUTE_READWRITE, &dwProtect);

	memcpy(result.SectionPtr, "\x90\x90\x90\x90", 4);
	result.CurrentPosition += 4;

	ms_PatcherData.ms_NumberOfRawMemorySections++;

	// Return this section
	return result;
}

RawMemorySubSection Patcher::RawMemoryMgr::MakeRawReturnJMP(RawMemorySubSection section, uintptr_t addr)
{
	RawMemorySection parent = section.__parent;

	BYTE jmp_e9 = 0xE9;
	section = WriteRawDataToSection(section, &jmp_e9, 1);

	DWORD movement = addr - ((DWORD)parent.SectionPtr + parent.CurrentPosition + section.CurrentSectionPos + 4);
	section = WriteRawDataToSection(section, &movement, sizeof(DWORD));

	ms_PatcherData.ms_NumberOfRawMemorySectionJMPs++;
	return section;
}

RawMemorySubSection Patcher::RawMemoryMgr::WriteRawDataToSection(RawMemorySubSection section, const void* value, size_t size)
{
	RawMemorySection parent_section = section.__parent;

	// Copy value in base pointer + current position (excluding sub section pos) + sub section pos
	memcpy(parent_section.SectionPtr + parent_section.CurrentPosition + section.CurrentSectionPos, value, size);
	section.CurrentSectionPos += size;
	return section;
}

RawMemorySubSection Patcher::RawMemoryMgr::MakeRawRelativeJMPaddr(RawMemorySubSection section, uintptr_t dest_addr)
{
	// Get parent section
	RawMemorySection parent = section.__parent;

	// jmp relative_offset
	DWORD result = dest_addr - (DWORD)(parent.SectionPtr + parent.CurrentPosition + section.CurrentSectionPos) - 4;
	return WriteRawDataToSection(section, &result, sizeof(DWORD));
}

RawMemorySubSection Patcher::RawMemoryMgr::MakeNewRawSubSection(RawMemorySection parent, uintptr_t SectionJumpAddr, uintptr_t SectionReturnAddr)
{
	RawMemorySubSection result;

	// Initialize sub section
	result.__parent = parent;
	result.SectionJumpAddress = SectionJumpAddr;
	result.SectionExitAddress = SectionReturnAddr;
	result.CurrentSectionPos = 0x0;

	ms_PatcherData.ms_NumberOfRawMemorySubSections++;

	return result;
}

// endpoint of RawDataSectionInfo
RawMemorySection Patcher::RawMemoryMgr::CloseThisRawDataSubSection(RawMemorySubSection section)
{
	RawMemorySection parent = section.__parent;

	// Make the final value in this subsection - the return jump
	section = MakeRawReturnJMP(section, section.SectionExitAddress);

	// Inject jump patch to this new raw data section - after that increase the current position and return the new raw memory section
	InjectFunctionPatch(section.SectionJumpAddress, parent.SectionPtr + parent.CurrentPosition, X86_FUNC_TYPE_JMP);

	// Make this section forbidden - and prevent UG's patching library from writing to this space in the future. Pretty pointless, but yeah, since I personally know I'm lazy, I decided to limit myself.
	MemorySection::DefineNewMemorySection(parent.SectionPtr + parent.CurrentPosition, parent.SectionPtr + parent.CurrentPosition + section.CurrentSectionPos, MEMORY_SEGMENT_FORBIDDEN);

	// Mark the end for this raw data sub section - this is because I want to seperate it - secret: it's not protected
	section = WriteRawDataToSection(section, "\x90\x90\x90\x90", 4);

	// Increase global raw memory section position with subsection position - which should re-align it, like stack
	parent.CurrentPosition += section.CurrentSectionPos;

	return parent;
}

//////////////////////////// END OF RAW MEMORY MANAGER CODE

//////////////////////////// START OF PATCHER LIST CODE

std::vector<std::function<void()>>* Patcher::PatcherList::function_list;

// Create a new lambda - containing a list of patcher functions - default patcher level
// Yeah its not done yet, rip
Patcher::PatcherList::PatcherList(std::function<void()> single_function)
{
	if (!function_list)
		function_list = new std::vector<std::function<void()>>;
	function_list->push_back(single_function);

	ms_PatcherData.ms_NumberOfPatcherLists++;
}

// Apply all of the lambda shit - loop through the list
void Patcher::PatcherList::ApplyAllPatcherLists()
{
	if (ms_PatcherData.bPatcherInitialized)
	{
		if (function_list)
		{
			for (auto function = function_list->cbegin(); function != function_list->cend(); function++)
			{
				(*function)();
				ms_PatcherData.ms_NumberOfPatchesAppliedFromPatcherLists++;
			}

			// Destroy the entire list because it is no longer needed
			delete function_list;
		}
	}
	else
	{
		// TODO: remove this?
		MessageBoxA(NULL, "Error: GTA: UG's patching library was not initialized, and a patcher list is attempted to be applied. Initialize the patcher before use.", "GTA: Underground", MB_OK);
		ExitProcess(0);
	}
}

//////////////////////////// END OF PATCHER LIST CODE

//////////////////////////// START OF MEMORY SECTION CODE

std::vector<MemorySegment> Patcher::MemorySection::MemorySections;

// Define new memory section
void Patcher::MemorySection::DefineNewMemorySection(uintptr_t start_addr, uintptr_t end_addr, uint8_t section_type)
{
	// Check every address untill it reaches the end address
	for (uintptr_t addr_index = start_addr; addr_index < end_addr; addr_index += 0x1)
	{
		if (GetMemorySectionForThisAddress(addr_index) != MEMORY_SEGMENT_STANDARD)
		{
			MessageBoxA(NULL, "Error: Attempt to define a memory section inside an already existing section.", "GTA: Underground", MB_OK);
			ExitProcess(0);
		}
	}

	MemorySegment result;

	result.start_addr = start_addr;
	result.end_addr = end_addr;
	result.segment_type = section_type;
	MemorySections.push_back(result);
}

// Define new memory section for function names
void Patcher::MemorySection::DefineNewMemorySection(void* start_addr, void* end_addr, uint8_t section_type)
{
	DefineNewMemorySection((uintptr_t)start_addr, (uintptr_t)end_addr, section_type);
}

// Get the memory section for this address
uint8_t Patcher::MemorySection::GetMemorySectionForThisAddress(uintptr_t addr)
{
	for (auto section = MemorySections.cbegin(); section != MemorySections.cend(); section++)
	{
		if (addr > section->start_addr && addr < section->end_addr)
		{
			return section->segment_type;
		}
	}

	// This memory address doesn't have a section! Return default.
	return MEMORY_SEGMENT_STANDARD;
}

uint8_t Patcher::MemorySection::GetMemorySectionForThisAddress(void* addr)
{
	return GetMemorySectionForThisAddress((uintptr_t)addr);
}

//////////////////////////// END OF MEMORY SECTION CODE

//////////////////////////// START OF PATCHER LEVEL CODE
// Not yet implemented because it is not needed.

void Patcher::PatcherLevel::EnterNewPatcherLevel()
{
	if (CurrentPatcherLevel + 1 > 127)
		MessageBoxA(NULL, "Error: Patcher level exceeds patcher level space!", "Patcher", MB_OK);
	PatcherLevelInfoArray[++CurrentPatcherLevel] = Info;
	ClearThisLevel();
}

void Patcher::PatcherLevel::EnterNewPatcherLevel(bool ObeyMemorySectionLaws, bool ApplyPatchesInThisLevel)
{
	if (CurrentPatcherLevel + 1 > 127)
		MessageBoxA(NULL, "Error: Patcher level exceeds patcher level space!", "Patcher", MB_OK);
	PatcherLevelInfoArray[++CurrentPatcherLevel] = Info;
	Info.ApplyPatchesInThisSection = ApplyPatchesInThisLevel;
	Info.ObeyMemorySectionRules = ObeyMemorySectionLaws;
}

void Patcher::PatcherLevel::LeaveThisPatcherLevel()
{
	// Restore old patcher info
	if (CurrentPatcherLevel <= 1)
		MessageBoxA(NULL, "Error: Patcher level is NULL", "Patcher", MB_OK);
	Info = PatcherLevelInfoArray[--CurrentPatcherLevel];
}

void Patcher::PatcherLevel::ClearThisLevel()
{
	Info.ApplyPatchesInThisSection = true;
	Info.ObeyMemorySectionRules = true;
	Info.ExecuteStepByStep = false;
}

int Patcher::PatcherLevel::GetCurrentPatcherLevel()
{
	return CurrentPatcherLevel;
}

//////////////////////////// END OF PATCHER LEVEL CODE

//////////////////////////// START OF GAME VERSION MANAGER

// Thanks to Silent & LINK2012!

// gets current game version
uint8_t Patcher::GameVersionMgr::GetCurrentGameVersion()
{
	if (!ms_PatcherData.ms_PatcherGameVersion)
	{
		if (ReadMemory<uint32_t>(0x82457C) == 0x94BF)
			ms_PatcherData.ms_PatcherGameVersion = GAME_VERSION_GTASA_US_1_0;
		else if (ReadMemory<uint32_t>(0x8245BC) == 0x94BF || ReadMemory<uint32_t>(0x8245B0) == 0x94BF)
			ms_PatcherData.ms_PatcherGameVersion = GAME_VERSION_GTASA_EU_1_0;
		else if (ReadMemory<uint32_t>(0x824570) == 0x94BF)
			ms_PatcherData.ms_PatcherGameVersion = GAME_VERSION_GTASA_US_1_0_COMPACT;
		else if (ReadMemory<uint32_t>(0x8252FC) == 0x94BF)
			ms_PatcherData.ms_PatcherGameVersion = GAME_VERSION_GTASA_US_1_1;
		else if (ReadMemory<uint32_t>(0x82533C) == 0x94BF)
			ms_PatcherData.ms_PatcherGameVersion = GAME_VERSION_GTASA_EU_1_1;
		else if (ReadMemory<uint32_t>(0x85EC4A) == 0x94BF)
			ms_PatcherData.ms_PatcherGameVersion = GAME_VERSION_GTASA_CRACKED_STEAM;
		else if (ReadMemory<uint32_t>(0xD3C3DB) == 0x94BF)
			ms_PatcherData.ms_PatcherGameVersion = GAME_VERSION_GTASA_ENCRYPTED_STEAM;

		// Hoodlum US and EU
		else if (ms_PatcherData.ms_PatcherGameVersion == GAME_VERSION_GTASA_EU_1_0 && ReadMemory<uint8_t>(0x406A20) == 0xE9)
			ms_PatcherData.ms_PatcherGameVersion = GAME_VERSION_GTASA_EU_1_0_HOODLUM;
		else if ((ms_PatcherData.ms_PatcherGameVersion == GAME_VERSION_GTASA_US_1_0 || ms_PatcherData.ms_PatcherGameVersion == GAME_VERSION_GTASA_US_1_0_COMPACT) && ReadMemory<uint8_t>(0x406A20) == 0xE9)
			ms_PatcherData.ms_PatcherGameVersion = GAME_VERSION_GTASA_US_1_0_HOODLUM;
	}
	return ms_PatcherData.ms_PatcherGameVersion;
}

uintptr_t Patcher::GameVersionMgr::GetAddressFromGameVersion(uintptr_t hoodlum_addr, uintptr_t _1_0_us_addr, bool ConvertUStoEU)
{
	uintptr_t real_1_0_addr = _1_0_us_addr;

	if (ConvertUStoEU && GetCurrentGameVersion() == GAME_VERSION_GTASA_EU_1_0)
		real_1_0_addr = ConvertAddressFromUStoEU(real_1_0_addr);
	else if (GetCurrentGameVersion() == GAME_VERSION_GTASA_US_1_0 || GetCurrentGameVersion() == GAME_VERSION_GTASA_EU_1_0)
		return real_1_0_addr;
	else if (GetCurrentGameVersion() == GAME_VERSION_GTASA_US_1_0_HOODLUM || GetCurrentGameVersion() == GAME_VERSION_GTASA_EU_1_0_HOODLUM)
		return hoodlum_addr;
}

uintptr_t Patcher::GameVersionMgr::GetAddressFromGameVersion(uintptr_t hoodlum_addr, uintptr_t _1_0_us_addr)
{
	return GetAddressFromGameVersion(hoodlum_addr, _1_0_us_addr, false);
}

uintptr_t Patcher::GameVersionMgr::ConvertAddressFromUStoEU(uintptr_t us_1_0_addr)
{
	if (GetCurrentGameVersion() == GAME_VERSION_GTASA_EU_1_0 && us_1_0_addr > 0x7466D0)
	{
		if (us_1_0_addr < 0x7BA940)
			us_1_0_addr += 0x50;
		else
			us_1_0_addr += 0x40;
	}
	return us_1_0_addr;
}

//////////////////////////// END OF GAME VERSION MANAGER

//////////////////////////// START OF PLUGIN PATCHER

// Returns NULL if error!
uintptr_t Patcher::PluginPatcher::GetPluginBaseAddress(const char* pluginName)
{
	uintptr_t result = (uintptr_t)GetModuleHandleA(pluginName);
	return result;
}

bool Patcher::PluginPatcher::ValidateFiles()
{
	return true;
}