#include <iostream>
#include <WiFiFrame.h>

int main()
{
	auto getData = WiFiFrame::parse("frames_phy.log");
	if (getData.second == 0)
	{
		auto result = WiFiFrame::processing(getData.first); 
		if(result.droneFrames.size() == 1294 && result.SSID == "Drone4E-2278faD" 
			&& result.MAC == "38e26e2278fa")
			std::cout << "Data successfully processed with no changes." << std::endl;
		else
			std::cout << "Data successfully processed with some changes." << std::endl;
	}
	else if (getData.second == -1)
		std::cout << "Error: Failed to open input file." << std::endl;
	else std::cout << "Error: Failed to parse input data. Error line: " << getData.second << std::endl;
}