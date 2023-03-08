#include <iostream>
#include "WiFiFrame.h"
#include <fstream>
#include <sstream>
#include <vector>

int main()
{
    std::ifstream input_file("frames_phy_test.log");
    if (!input_file.is_open()) {
        std::cout << "Error: failed to open input file." << std::endl;
        return 1;
    }

    std::vector<WiFiFrame> frames; // a vector to hold the WiFiFrame objects

    std::string line;
    while (getline(input_file, line)) {
        std::istringstream ss(line); 
        WiFiFrame frame; 

        // parsing


        frames.push_back(frame); // add the WiFiFrame object to the vector
    };

    input_file.close(); 

    // check
    std::cout << "id: " << frames[0].id << std::endl;
    std::cout << "offset: " << frames[0].offset << std::endl;
    std::cout << "bw: " << frames[0].bandWidth << std::endl;
    std::cout << "mcs: " << frames[0].mcs << std::endl;
    std::cout << "size: " << frames[0].size << std::endl;
    std::cout << "bits: " << frames[0].bits << std::endl;
    std::cout << std::endl;
    return 0;
}