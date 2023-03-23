#include <iostream>
#include "WiFiFrame.h"
#include <fstream>
#include <sstream>
#include <vector>

int main()
{
    std::ifstream input_file("frames_phy.log");
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
            std::string bits_hex;
            ss >> frame.id;
            ss.ignore(1); // skip the tab character
            std::string offset_str;
            getline(ss, offset_str, ',');
            frame.offset = stod(offset_str.substr(7)); // skip "Offset=" prefix
            std::string bw_str;
            getline(ss, bw_str, ',');
            frame.bandWidth = stoi(bw_str.substr(3)); // skip "BW=" prefix
            std::string mcs_str;
            getline(ss, mcs_str, ',');
            int lparen_idx = mcs_str.find('(');
            int rparen_idx = mcs_str.find(')');
            std::string mcs_num_str = mcs_str.substr(0, lparen_idx);
            frame.mcs = stoi(mcs_num_str.substr(4)); // skip "MCS=" prefix
            std::string size_str;
            getline(ss, size_str, ',');
            frame.size = stoi(size_str.substr(5)); // skip "Size=" prefix
            ss >> bits_hex;
            for (int i = 0; i < bits_hex.length(); i += 2) {
                std::string byte_hex = bits_hex.substr(i, 2);
                int byte = stoi(byte_hex, nullptr, 16);
                frame.bits += (char)byte;
            }

            frames.push_back(frame); // add the WiFiFrame object to the vector
        }
 
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