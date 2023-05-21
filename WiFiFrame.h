#pragma once

#include <string>
#include <map>
#include <cstdint>
#include <sstream>
#include <iomanip>
#include <bitset>

class WiFiFrame
{
public:

	struct MCS
	{
		uint8_t value;
		std::string standart;
		std::string scheme;
		uint8_t speed_mbps;
	};

	uint32_t id;
	double offset;
	uint8_t bandWidth;
	MCS mcs;
	size_t size;
	std::string bits;

	WiFiFrame();

	WiFiFrame(uint32_t id, double offset, uint8_t bandWidth, MCS mcs, size_t size, std::string bits);
	
	~WiFiFrame();

	static uint8_t* dataToByteArray(const std::string hexStr, std::size_t size);

	static std::string hexToBinary(const std::string& hex);

	static uint32_t calculateCRC32(const uint8_t* data, std::size_t size);

	static bool checkCRC32(const std::string hexStr, std::size_t size);

	short int getType();

	bool isBeacon();

	std::string getBeaconSSID();

	static bool compareSSID(std::string SSID);

	std::string getSA();

private:

};

