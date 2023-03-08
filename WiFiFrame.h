#pragma once

#include <string>

class WiFiFrame
{
public:
	int id;
	double offset;
	short int bandWidth;
	std::string mcs;
	//struct mcs
	//{
	//	short int value;
	//	std::string standart;
	//	short int QAM;
	//	std::string FEC;
	//	short int speed;
	//};
	short int size;
	std::string bits;
};

