#pragma once

#include <iostream>
#include <string>
#include <map>
#include <cstdint>
#include <sstream>
#include <iomanip>
#include <bitset>
#include <fstream>
#include <vector>

class WiFiFrame
{
public:

	uint32_t id;
	float offset;
	uint16_t bandWidth;
	uint16_t mcs;
	std::string modulation;
	uint32_t size;
	std::string bits;

	struct processingResult
	{
		std::vector <WiFiFrame> droneFrames;
		std::string SSID;
		std::string MAC;
	};

	WiFiFrame();

	WiFiFrame(uint32_t id, float offset, uint16_t bandWidth, uint16_t mcs, std::string modulation, uint32_t size, std::string bits);
	
	~WiFiFrame();

	static std::pair<std::vector<WiFiFrame>, uint32_t> parse(const std::string fileName);

	static bool checkCRC32(const std::string hexStr, std::size_t size);

	static processingResult processing(std::vector<WiFiFrame> data);

	static void writeToFile(std::vector <WiFiFrame>& drone_frames, const std::string fileName);

	short int getType();

	bool isBeacon();

	std::string getBeaconSSID();

	static bool compareSSID(std::string SSID);

	std::string getSA();

private:

	static bool isNumeric(const std::string& str) {
		for (char c : str) {
			if (!std::isdigit(c) && c != '.') {
				return false;
			}
		}
		return true;
	}

	static uint8_t* dataToByteArray(const std::string hexStr, std::size_t size);

	static std::string hexToBinary(const std::string& hex);

	static uint32_t calculateCRC32(const uint8_t* data, std::size_t size);
};

