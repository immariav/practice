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
	short int size;
	std::string bits;

private:

};

