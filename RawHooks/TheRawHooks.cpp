#include "../Shared.hpp"
#include "TheRawHooks.h"

uint8_t* TheRawHooks::ms_pTheRawHooks;
uint32_t TheRawHooks::ms_nGlobalPos;
std::vector<RawHookVariable*> TheRawHooks::m_vVariables;

bool TheRawHooks::Initialize()
{
	ms_pTheRawHooks = new uint8_t[THERAWHOOKS_SPACE];
	if (ms_pTheRawHooks)
	{
		ms_nGlobalPos = 0;
		return true;
	}
	else
	{
		return false;
	}
}

// Replaces all occurences in a string from szFrom to szTo
void TheRawHooks::ReplaceAllInString(std::string& szTargetStr, const std::string& szFrom, const std::string& szTo)
{
	size_t nStartPos = 0;

	if (szFrom.empty())
	{
		return;
	}
	else
	{
		while ((nStartPos = szTargetStr.find(szFrom, nStartPos)) != std::string::npos)
		{
			szTargetStr.replace(nStartPos, szFrom.length(), szTo);
			nStartPos += szTo.length();
		}
	}
}

void TheRawHooks::StaticRawHook(uint32_t dwJumpFrom, std::string szBytes, uint32_t dwJumpTo)
{
	// Construct a RawHook
	RawHook m_Hook(dwJumpFrom, dwJumpTo);
	m_Hook.Start();

	// Get rid of all spaces between stuff
	ReplaceAllInString(szBytes, " ", "");

	// Scan the string for any keywords

	// Scan the string for any variables
	// TODO: make it so multiple variable keywords of the same name are found and replaced (VERY important)
	for (uint32_t i = 0; i < m_vVariables.size(); i++)
	{
		switch (m_vVariables[i]->m_eType)
		{
		case RAWHOOKVARIABLE_BYTE:
			if (szBytes.find(m_vVariables[i]->m_szVariableName))
			{
				char m_Hex[512];
				sprintf(m_Hex, "%X", m_vVariables[i]->m_bValue);
				szBytes.replace(szBytes.find(m_vVariables[i]->m_szVariableName), m_vVariables[i]->m_szVariableName.size(), m_Hex);
			}
			break;

		case RAWHOOKVARIABLE_WORD:
			if (szBytes.find(m_vVariables[i]->m_szVariableName))
			{
				char m_Hex[512];
				sprintf(m_Hex, "%X", m_vVariables[i]->m_wValue);
				szBytes.replace(szBytes.find(m_vVariables[i]->m_szVariableName), m_vVariables[i]->m_szVariableName.size(), m_Hex);
			}
			break;

		case RAWHOOKVARIABLE_DWORD:
			if (szBytes.find(m_vVariables[i]->m_szVariableName))
			{
				char m_Hex[512];
				sprintf(m_Hex, "%X", m_vVariables[i]->m_dwValue);
				szBytes.replace(szBytes.find(m_vVariables[i]->m_szVariableName), m_vVariables[i]->m_szVariableName.size(), m_Hex);
			}
			break;

		case RAWHOOKVARIABLE_FLOAT:
			if (szBytes.find(m_vVariables[i]->m_szVariableName))
			{
				char m_Hex[512];
				sprintf(m_Hex, "%X", m_vVariables[i]->m_fValue);
				szBytes.replace(szBytes.find(m_vVariables[i]->m_szVariableName), m_vVariables[i]->m_szVariableName.size(), m_Hex);
			}
			break;
		}
	}

	// Create a byte array from the string
	uint8_t* bBytes = new uint8_t[szBytes.size()];

	for (uint32_t i = 0; i < szBytes.size(); i++)
	{
		bBytes[i] = szBytes[i];
	}

	// Write the newly created data to the rawhook
	m_Hook.Write(bBytes, szBytes.size());

	// Finish the newly created RawHook
	m_Hook.Finish();
}

void TheRawHooks::StaticRawHook(Memory* pJumpFrom, std::string szBytes, Memory* pJumpTo)
{
	// Construct a RawHook
	RawHook m_Hook(pJumpFrom->GetAddress(), pJumpTo->GetAddress());
	m_Hook.Start();

	// Get rid of all spaces between stuff
	ReplaceAllInString(szBytes, " ", "");

	// Scan the string for any keywords

	// Scan the string for any variables
	// TODO: make it so multiple variable keywords of the same name are found and replaced (VERY important)
	for (uint32_t i = 0; i < m_vVariables.size(); i++)
	{
		switch (m_vVariables[i]->m_eType)
		{
		case RAWHOOKVARIABLE_BYTE:
			if (szBytes.find(m_vVariables[i]->m_szVariableName))
			{
				char m_Hex[512];
				sprintf(m_Hex, "%X", m_vVariables[i]->m_bValue);
				szBytes.replace(szBytes.find(m_vVariables[i]->m_szVariableName), m_vVariables[i]->m_szVariableName.size(), m_Hex);
			}
			break;

		case RAWHOOKVARIABLE_WORD:
			if (szBytes.find(m_vVariables[i]->m_szVariableName))
			{
				char m_Hex[512];
				sprintf(m_Hex, "%X", m_vVariables[i]->m_wValue);
				szBytes.replace(szBytes.find(m_vVariables[i]->m_szVariableName), m_vVariables[i]->m_szVariableName.size(), m_Hex);
			}
			break;

		case RAWHOOKVARIABLE_DWORD:
			if (szBytes.find(m_vVariables[i]->m_szVariableName))
			{
				char m_Hex[512];
				sprintf(m_Hex, "%X", m_vVariables[i]->m_dwValue);
				szBytes.replace(szBytes.find(m_vVariables[i]->m_szVariableName), m_vVariables[i]->m_szVariableName.size(), m_Hex);
			}
			break;

		case RAWHOOKVARIABLE_FLOAT:
			if (szBytes.find(m_vVariables[i]->m_szVariableName))
			{
				char m_Hex[512];
				sprintf(m_Hex, "%X", m_vVariables[i]->m_fValue);
				szBytes.replace(szBytes.find(m_vVariables[i]->m_szVariableName), m_vVariables[i]->m_szVariableName.size(), m_Hex);
			}
			break;
		}
	}

	// Create a byte array from the string
	uint8_t* bBytes = new uint8_t[szBytes.size()];

	for (uint32_t i = 0; i < szBytes.size(); i++)
	{
		bBytes[i] = szBytes[i];
	}

	// Write the newly created data to the rawhook
	m_Hook.Write(bBytes, szBytes.size());

	// Finish the newly created RawHook
	m_Hook.Finish();
}

bool TheRawHooks::Shutdown()
{
	if (ms_pTheRawHooks)
	{
		free(ms_pTheRawHooks);
	}
	return true;
}