#include <iostream>
#include <WiFiFrame.h>

bool areFilesSameContent(const std::string& file1Path, const std::string& file2Path) 
{
    std::ifstream f1(file1Path);
    std::ifstream f2(file2Path);
    char c1, c2;
    while (true) 
    {
        c1 = f1.get();
        c2 = f2.get();
        if (c1 != c2) 
            return false;
        
        if (f1.eof() || f2.eof())
            break;
    }
    if (f1.eof() && f2.eof())
        return true;
    f1.close();
    f2.close();
}

int main()
{
	auto getData = WiFiFrame::parse("input.log");
	if (getData.second == 0)
	{
		auto result = WiFiFrame::processing(getData.first);
		WiFiFrame::writeToFile(result.droneFrames, "output.log");
		if(result.droneFrames.size() == 1294 && result.SSID == "Drone4E-2278faD" 
			&& result.MAC == "38e26e2278fa" && areFilesSameContent("output.log", "expected_result.log"))
			std::cout << "Data successfully processed with no changes." << std::endl;
		else
			std::cout << "Data successfully processed with some changes." << std::endl;
	}
	else if (getData.second == -1)
		std::cout << "Error: Failed to open input file." << std::endl;
	else std::cout << "Error: Failed to parse input data. Error line: " << getData.second << std::endl;
}