#include "WiFiFrame.h"

int main()
{
	auto getData = WiFiFrame::parse("frames_phy.log");
	if (getData.second == 0)
	{
		auto result = WiFiFrame::processing(getData.first);
		WiFiFrame::writeToFile(result.first, "output.log");
	}
	else if (getData.second == -1)
		std::cout << "Error: Failed to open input file." << std::endl;
	else std::cout << "Error: Failed to parse input data. Error line: " << getData.second << std::endl;
}
