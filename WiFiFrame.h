#pragma once

#include <string>

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

	int id;
	double offset;
	short int bandWidth;
	MCS mcs;
	size_t size;
	std::string bits;

	WiFiFrame();

	WiFiFrame(int id, double offset, short int bandWidth, MCS mcs, size_t size, std::string bits);
	
	~WiFiFrame();

	static uint32_t calculateCRC32( const uint8_t* data, std::size_t size );

	static bool checkCRC32( const std::string hexStr, std::size_t size );

private:

};

