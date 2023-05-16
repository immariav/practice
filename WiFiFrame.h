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
		short int value;
		std::string standart;
		std::string scheme;
		short int speed_mbps;
	};

	uint32_t id;
	double offset;
	short int bandWidth;
	MCS mcs;
	size_t size;
	std::string bits;

	WiFiFrame();

	WiFiFrame(uint32_t id, double offset, short int bandWidth, MCS mcs, size_t size, std::string bits);
	
	~WiFiFrame();

	static uint8_t* dataToByteArray(const std::string hexStr, std::size_t size);

	static std::string hexToBinary(const std::string& hex)
	{
		std::stringstream ss;
		for (size_t i = 0; i < hex.length(); ++i) {
			uint8_t byte = std::stoi(hex.substr(i, 2), nullptr, 16);
			ss << std::bitset<8>(byte);
		}
		return ss.str();
	}

	static uint32_t calculateCRC32(const uint8_t* data, std::size_t size);

	static bool checkCRC32(const std::string hexStr, std::size_t size);

	short int getType();

	bool isBeacon();

private:

};

