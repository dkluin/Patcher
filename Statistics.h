#pragma once

#include <stdint.h>
#include <string>
#include <vector>

#define SHOULD_USE_STATS


#ifdef SHOULD_USE_STATS
class Stat
{
private:
	std::string m_szStatName;
	uint32_t m_dwValue;

public:
	Stat(std::string m_szStat, uint32_t m_dwValue)
	{
		this->m_szStatName = m_szStat;
		this->m_dwValue = m_dwValue;
	}

	~Stat()
	{
		// TODO....
	}
};

class Statistics
{
private:
	static std::vector<Stat> ms_vPatcherStats;

public:
	// Increase statistic
	static void IncreasePatchingStat(std::string m_szStatName, uint32_t m_dwValue);

	// Decrease statistic
	static void DecreasePatchingStat(std::string m_szStatName, uint32_t m_dwValue);

	// Gets the value of a stat
	static uint32_t GetStatValue(std::string m_szStatName);

	// Initialize statistic slots
	static void InitializeStats();
};
#endif