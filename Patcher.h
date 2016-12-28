#pragma once
#include <cstdint>
#include <cstddef>
#include <functional>
#include <type_traits>
#include <initializer_list>
#include <Windows.h>
#include <vector>
#include "PatcherInfo.h"

//// Typedefs

typedef uint8_t x86_func_type; // JMP or CALL, only for inject function patch!
typedef uint16_t x86_jmp_type; // JMP type patches

//// Macro's

#define X86_PUSHAD _asm pushad
#define X86_POPAD _asm popad

// temp!
//
//	ASM EPILOG and ASM PROLOG macros
//
#define ASM_PROLOG() _asm					\
	{										\
		_asm push	ebp						\
		_asm mov	ebp, esp				\
		_asm sub	esp, __LOCAL_SIZE		\
	}

#define ASM_EPILOG() _asm					\
	{										\
		_asm mov	esp, ebp				\
		_asm pop	ebp						\
	}
//// Enums

enum x86_function_types
{
	X86_FUNC_TYPE_DEFAULT = 0,
	X86_FUNC_TYPE_JMP = 1,
	X86_FUNC_TYPE_CALL = 2
};

enum x86_JMP_instruction_type
{
	X86_JMP_TYPE_DEFAULT = 0xE9,

	X86_JMP_TYPE_JO = 0x0F80,
	X86_JMP_TYPE_JNO = 0x0F81,

	X86_JMP_TYPE_JB = 0x0F82,
	X86_JMP_TYPE_JNAE = 0x0F82,
	X86_JMP_TYPE_JC = 0x0F82,

	X86_JMP_TYPE_JNB = 0x0F83,
	X86_JMP_TYPE_JAE = 0x0F83,
	X86_JMP_TYPE_JNC = 0x0F83,

	X86_JMP_TYPE_JE = 0x0F84,
	X86_JMP_TYPE_JZ = 0x0F84,

	X86_JMP_TYPE_JNE = 0x0F85,
	X86_JMP_TYPE_JNZ = 0x0F85,

	X86_JMP_TYPE_JBE = 0x0F86,
	X86_JMP_TYPE_JNA = 0x0F86,

	X86_JMP_TYPE_JA = 0x0F87,
	X86_JMP_TYPE_JNBE = 0x0F87,

	X86_JMP_TYPE_JS = 0x0F88,

	X86_JMP_TYPE_JNS = 0x0F89,

	X86_JMP_TYPE_JP = 0x0F8A,
	X86_JMP_TYPE_JPE = 0x0F8A,

	X86_JMP_TYPE_JNP = 0x0F8B,
	X86_JMP_TYPE_JPO = 0x0F8B,

	X86_JMP_TYPE_JL = 0x0F8C,
	X86_JMP_TYPE_JNGE = 0x0F8C,

	X86_JMP_TYPE_JGE = 0x0F8D,
	X86_JMP_TYPE_JNL = 0x0F8D,

	X86_JMP_TYPE_JLE = 0x0F8E,
	X86_JMP_TYPE_JNG = 0x0F8E,

	X86_JMP_TYPE_JG = 0x0F8F,
	X86_JMP_TYPE_JNLE = 0x0F8F
};

enum X86_Raw_JMP_function_types
{
	X86_RAW_JMP_FUNC_TYPE_DEFAULT = 0,

	X86_RAW_JMP_FUNC_TYPE_JO = 1,
	X86_RAW_JMP_FUNC_TYPE_JNO = 1,

	X86_RAW_JMP_FUNC_TYPE_JB = 2,
	X86_RAW_JMP_FUNC_TYPE_JNAE = 2,
	X86_RAW_JMP_FUNC_TYPE_JC = 2,

	X86_RAW_JMP_FUNC_TYPE_JNB = 3,
	X86_RAW_JMP_FUNC_TYPE_JAE = 3,
	X86_RAW_JMP_FUNC_TYPE_JNC = 3,

	X86_RAW_JMP_FUNC_TYPE_JE = 4,
	X86_RAW_JMP_FUNC_TYPE_JZ = 4,

	X86_RAW_JMP_FUNC_TYPE_JNE = 5,
	X86_RAW_JMP_FUNC_TYPE_JNZ = 5,

	X86_RAW_JMP_FUNC_TYPE_JBE = 6,
	X86_RAW_JMP_FUNC_TYPE_JNA = 6,

	X86_RAW_JMP_FUNC_TYPE_JA = 7,
	X86_RAW_JMP_FUNC_TYPE_JNBE = 7,

	X86_RAW_JMP_FUNC_TYPE_JS = 8,

	X86_RAW_JMP_FUNC_TYPE_JNS = 9,

	X86_RAW_JMP_FUNC_TYPE_JP = 10,
	X86_RAW_JMP_FUNC_TYPE_JPE = 10,

	X86_RAW_JMP_FUNC_TYPE_JNP = 11,
	X86_RAW_JMP_FUNC_TYPE_JPO = 12,

	X86_RAW_JMP_FUNC_TYPE_JL = 13,
	X86_RAW_JMP_FUNC_TYPE_JNGE = 13,

	X86_RAW_JMP_FUNC_TYPE_JGE = 14,
	X86_RAW_JMP_FUNC_TYPE_JNL = 14,

	X86_RAW_JMP_FUNC_TYPE_JLE = 15,
	X86_RAW_JMP_FUNC_TYPE_JNG = 15,

	X86_RAW_JMP_FUNC_TYPE_JG = 16,
	X86_RAW_JMP_FUNC_TYPE_JNLE = 16
};

enum eGameVersion : uint8_t
{
	GAME_VERSION_UNKNOWN,
	GAME_VERSION_GTASA_EU_1_0_HOODLUM,
	GAME_VERSION_GTASA_US_1_0_HOODLUM,
	GAME_VERSION_GTASA_US_1_0,
	GAME_VERSION_GTASA_EU_1_0,
	GAME_VERSION_GTASA_US_1_0_COMPACT,
	GAME_VERSION_GTASA_US_1_1,
	GAME_VERSION_GTASA_EU_1_1,
	GAME_VERSION_GTASA_CRACKED_STEAM,
	GAME_VERSION_GTASA_ENCRYPTED_STEAM
};

enum x86_Memory_Segment_Types
{
	// Default segment, it has read/write/execute permission
	MEMORY_SEGMENT_STANDARD = 0,

	// Read only, ANY write function is disabled in this section
	MEMORY_SEGMENT_READONLY = 1,

	// Write only, ANY read function is disabled in this section
	MEMORY_SEGMENT_WRITEONLY = 2,

	// Forbidden, prevent ANY patcher function from writing data to this space. 
	MEMORY_SEGMENT_FORBIDDEN = 3,
};

struct MemorySegment
{
	// Start address
	uintptr_t start_addr;

	// End address
	uintptr_t end_addr;

	// Segment type
	uint8_t segment_type;
};

struct PatcherLevelInfo
{
	bool ApplyPatchesInThisSection;
	bool ObeyMemorySectionRules;
	bool ExecuteStepByStep;
};

class RegisterStorage
{
public:
	DWORD EAX;
	DWORD EBX;
	DWORD ECX;
	DWORD EDX;
	DWORD ESI;
	DWORD EDI;
};

class RawMemorySection
{
public:
	// Address of raw memory section
	BYTE *SectionPtr;

	// Current position in section
	uint32_t CurrentPosition;

	// Size
	size_t RawDataSectionSize;
};

class RawMemorySubSection
{
public:
	// Parent memory section - used to get the position
	RawMemorySection __parent;

	// Position in subsection, offset to global section position
	uint32_t CurrentSectionPos;

	// Address where code jumps to this subsection
	uintptr_t SectionJumpAddress;

	// Address where code exits this section
	uintptr_t SectionExitAddress;
};

class Patcher
{
public:
	// init
	static bool Initialize();

	// NOP vars
	static void NOPData(uintptr_t addr, int size);

	// Patch on address - just like hax! - works
	template<class T>
	static void PatchOnAddress(uintptr_t addr, T value)
	{
		if (MemorySection::GetMemorySectionForThisAddress(addr) == MEMORY_SEGMENT_STANDARD ||
			MemorySection::GetMemorySectionForThisAddress(addr) == MEMORY_SEGMENT_WRITEONLY)
		{
			WriteDataToMemory((void*)addr, &value, sizeof(value));

			ms_PatcherData.ms_NumberOfMemoryPatches++;
			ms_PatcherData.ms_TotalNumberOfMemoryChanges++;
		}
	};

	// Patch multiple - works
	template<class T>
	static void PatchMultipleAddr(T value, std::initializer_list<uintptr_t> addr2)
	{
		for (auto addr : addr2)
		{
			if (MemorySection::GetMemorySectionForThisAddress(addr) == MEMORY_SEGMENT_STANDARD ||
				MemorySection::GetMemorySectionForThisAddress(addr) == MEMORY_SEGMENT_WRITEONLY)
			{
				WriteDataToMemory((void*)addr, &value, sizeof(value));

				ms_PatcherData.ms_NumberOfMemoryPatches++;
				ms_PatcherData.ms_TotalNumberOfMemoryChanges++;
			}
		}
	};

	// Useful when replacing call functions with a function which returns a specific value.
	template<class T, T value>
	static T ReturnValue(T value)
	{
		return value;
	}

	// Calculate JMP address - reads an offset on @offset, the instruction address @addr and returns the JMP address.
	static uintptr_t CalculateJMPaddress(uintptr_t addr);

	// Make RET
	static void WriteRET(uintptr_t addr);

	// MemCpy with unprotection of address
	static void MemCpy(uintptr_t addr, const void* dest, size_t size);

	// MemSet with unprotection of address
	static void MemSet(uintptr_t addr, int32_t value, size_t size);

	// Read memory of any type - but ONLY if the patcher is allowed to
	template<class T>
	static T ReadMemory(uintptr_t addr)
	{
		T result = 0;

		if (MemorySection::GetMemorySectionForThisAddress(addr) == MEMORY_SEGMENT_STANDARD ||
			MemorySection::GetMemorySectionForThisAddress(addr) == MEMORY_SEGMENT_READONLY)
		{
			DWORD dwProtect[2];
			VirtualProtect((PVOID)addr, sizeof(T), PAGE_EXECUTE_READWRITE, &dwProtect[0]);
			memcpy(&result, (PVOID)addr, sizeof(T));
			VirtualProtect((PVOID)addr, sizeof(T), dwProtect[0], &dwProtect[1]);
		}
		return result;
	};

	static void InjectFunctionPatchOnMultipleAddresses(void* dest_addr, x86_func_type type, std::initializer_list<uintptr_t> addr2);
	static void InjectFunctionPatchOnMultipleAddresses(uintptr_t dest_addr, x86_func_type type, std::initializer_list<uintptr_t> addr2);

	// Inject function - asm patches
	static void InjectFunctionPatch(uintptr_t addr, void* function_name, x86_func_type type);	// Patch a function - inject JMP/CALL
	static void InjectFunctionPatch(uintptr_t addr, uintptr_t redirect_addr, x86_func_type type);

	// Inject JMP function - was missing for whatever reason, maybe bad organizing? idfk...
	// Do note: doesn't handle JMP/CALL, for that, use InjectFunctionPatch! Only handles all other JMP functions.
	static void InjectJMPpatch(uintptr_t src, void* dest, x86_jmp_type type);
	static void InjectJMPpatch(uintptr_t src, uintptr_t dest, x86_jmp_type type);

	template <class T>
	static void SetMemoryToValue(void* addr, T value, size_t size)
	{
		if (MemorySection::GetMemorySectionForThisAddress(addr) == MEMORY_SEGMENT_STANDARD ||
			MemorySection::GetMemorySectionForThisAddress(addr) == MEMORY_SEGMENT_WRITEONLY)
		{
			WriteDataToMemory(addr, &value, size);

			ms_PatcherData.ms_TotalNumberOfMemoryChanges++;
		}
	}

	// Custom MemSet function, used for setting raw memory of variable size. This is a custom function used to set large segments of data with NULLs, for example.
	template <class T>
	static void SetMemoryToValue(uintptr_t addr, T value, size_t size)
	{
		SetMemoryToValue((void*)addr, value, size);
	}

	// Fill this memory area with pure zeroes.
	static void FillMemoryWithZeroes(uintptr_t addr, size_t size);
	static void FillMemoryWithZeroes(void* addr, size_t size);

	////////// Raw functions
	////////// This is used for defining raw bytes of data, often instructions, and making jumps to and from this space. NOTE: ALL subsections are forbidden memory sections.
	////////// Because of this, you won't be able to modify/overwrite it, atleast from UG's end.

	class RawMemoryMgr
	{
	public:
		// Make raw patch - which is put in dynamic memory space
		static RawMemorySubSection WriteRawDataToSection(RawMemorySubSection section, const void* value, size_t size);

		// Allocate a new raw data section
		static RawMemorySection AllocateNewRawDataSection(size_t size);

		// Close raw function and return - returns updated RawMemorySection, because sub section functions changed it!
		static RawMemorySection CloseThisRawDataSubSection(RawMemorySubSection section);

		// Make new subsection
		static RawMemorySubSection MakeNewRawSubSection(RawMemorySection parent, uintptr_t SectionJumpAddr, uintptr_t SectionReturnAddr);

		// Make a return jump 
		static RawMemorySubSection MakeRawReturnJMP(RawMemorySubSection section, uintptr_t addr);

		// Make a relative address - like FLA does
		static RawMemorySubSection MakeRawRelativeJMPaddr(RawMemorySubSection section, uintptr_t destination);
	};

	////////// End of raw functions
	////////// Patching lists, a list of multiple patches all executed neatly in a list. Memory section rules still apply no matter what. 

	class PatcherList
	{
	private:
		// A list of all lambda-ish functions.
		static std::vector<std::function<void()>>* function_list;

	public:

		// Create a new patcher list - with default patcher level setting.
		PatcherList(std::function<void()> single_function);

		// Apply all of the lists.
		static void ApplyAllPatcherLists();
	};

	////////// End of patching lists

	////////// Memory sections code, prevent patcher from writing data to protected area's. 
	////////// The actual point of this system is to prevent the patcher from overwriting reversed function data. 
	class MemorySection
	{
	public:
		// Checks if this address is protected
		static uint8_t GetMemorySectionForThisAddress(uintptr_t addr);
		static uint8_t GetMemorySectionForThisAddress(void* addr);

		// Make a new protected memory space
		static void DefineNewMemorySection(uintptr_t start_addr, uintptr_t end_addr, uint8_t section_type);
		static void DefineNewMemorySection(void* start_addr, void* end_addr, uint8_t section_type);

		// List of protected memory
	private:
		static std::vector<MemorySegment> MemorySections;
	};

	////////// End of memory section code

	////////// Patcher level

	////////// Currently disabled, should be correctly implemented in library. 
	////////// Purpose: have full control over which patcher lists are executed and which arent. 
	////////// This means a new patcher level is ALWAYS entered once a new lamba is defined. 
	////////// It is also possible to define a new patcher level for normal functions. 

	class PatcherLevel
	{

	public:
		// Enter new level, no specific info, reset old
		static void EnterNewPatcherLevel();

		// Enter level, but set info
		static void EnterNewPatcherLevel(bool ObeyMemorySectionLaws, bool ApplyPatchesInThisLevel);

		// Go back one level
		static void LeaveThisPatcherLevel();

		// Push this patcher level info onto the array - but clear it
		static void ClearThisLevel();

		// Get current patcher level
		static int GetCurrentPatcherLevel();

		// Current level
		static int CurrentPatcherLevel;

	private:
		// Patcher level info array - the index value is determined by EnterNewPatcherLevel() and LeaveThisPatcherLevel(). In other words, the index value CurrentPatcherLevel holds the current
		// patcher level. It is possible to change the patcher level info at runtime......
		static PatcherLevelInfo PatcherLevelInfoArray[128];

		// Current level INFO
		static PatcherLevelInfo Info;
	};

	////////// End of patcher level code
	////////// Start of game version manager
	//////////
	////////// Unfortunately, not fully implemented.
	////////// I'll add it soon!!!!!!

	class GameVersionMgr
	{
	public:
		// Get current game version, should be executed BEFORE patching
		static uint8_t GetCurrentGameVersion();

		// Get address based on game version - hoodlum & 1.0 only (it converts US to EU if game version is EU aswell)
		static uintptr_t GetAddressFromGameVersion(uintptr_t hoodlum_addr, uintptr_t _1_0_us_addr, bool ConvertUStoEU);	

		// Same as above, but do not convert address - used when this address is certain to be a 1.0 US address, NOT an EU one!
		static uintptr_t GetAddressFromGameVersion(uintptr_t hoodlum_addr, uintptr_t _1_0_us_addr);	

		// Convert an address value from US 1.0 to EU 1.0
		static uintptr_t ConvertAddressFromUStoEU(uintptr_t us_1_0_addr);
	};

	////////// End of game version manager code

	////////// Start of plugin patcher code
	//////////
	////////// Contains a few useful functions for getting an address of a function in an ASI/DLL. 
	////////// Return value is an uintptr_t address which can then be used to patch whatever is necessary in said dll/asi.
	class PluginPatcher
	{
	public:
		// Returns the base address
		static uintptr_t GetPluginBaseAddress(const char* pluginName);
	};

	/////////// End of plugin patcher code
	
	/////////// Start of function calling code
	///////////
	/////////// Useful functions for calling functions on addresses
	class FunctionCalling
	{
	public:
		// Standard function calling
		template<class Ret, class ...Args>
		static Ret Call(uintptr_t p, Args... a)
		{
			auto fn = (Ret(*)(Args...)) p;
			ms_PatcherData.ms_CalledFunctions++;
			return fn(std::forward<Args>(a)...);
		}

		// ThisCall
		template<class Ret, class ...Args>
		static Ret ThisCall(uintptr_t p, Args... a)
		{
			auto fn = (Ret(__thiscall*)(Args...)) p;
			ms_PatcherData.ms_CalledFunctions++;
			return fn(std::forward<Args>(a)...);
		}
	};

	// general
	static void PatchMemData(uintptr_t addr, const void* data, int size);
	static void WriteDataToMemory(void* addr, const void* data, int size);

	static PatcherInfo ms_PatcherData;
};
