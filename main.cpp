#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "WiFiFrame.h"
#include <map>

std::vector<WiFiFrame> parsing(std::string fileName);

int main()
{
    std::vector<WiFiFrame> frames = parsing("frames_phy.log");

    std::vector<WiFiFrame> frames_sorted;

    std::vector<WiFiFrame> data_frames; // a vector to hold data frames for the last task

    for (size_t i = 0; i < frames.size(); i++)
    {
        if (WiFiFrame::checkCRC32(frames[i].bits, frames[i].size))
            frames_sorted.push_back(frames[i]);
    }

    frames.clear(); 
    frames.shrink_to_fit(); 

    std::map<std::string, std::string> dronesSSID_MAC; // a map to hold drones' SSIDs with their MACs

    for (size_t i = 0; i < frames_sorted.size(); i++)
    {
        if (frames_sorted[i].getType() == 0)
        {
            if (frames_sorted[i].isBeacon())
            {
                std::string SSID = frames_sorted[i].getBeaconSSID();
                if(WiFiFrame::compareSSID(SSID))
                {
                    dronesSSID_MAC.insert(std::make_pair(SSID, frames_sorted[i].getSA()));
                }
            }
        }
        if (frames_sorted[i].getType() == 2)
            data_frames.push_back(frames_sorted[i]);
    }

    frames_sorted.clear();
    frames_sorted.shrink_to_fit();

    std::vector<WiFiFrame> drone_frames;

    for (size_t i = 0; i < data_frames.size(); i++)
    {
       for (const auto& pair : dronesSSID_MAC) 
       {
            if (pair.second == data_frames[i].getSA())
                {
                    drone_frames.push_back(data_frames[i]);
                    break;
                }
            }
    }

    data_frames.clear();
    data_frames.shrink_to_fit();

    std::cout << drone_frames.size() << std::endl;
}

std::vector<WiFiFrame> parsing(std::string fileName)
{
    std::ifstream input_file(fileName);
    if (!input_file.is_open()) 
        throw std::invalid_argument("Error: failed to open input file.");

    std::vector<WiFiFrame> frames; // a vector to hold the WiFiFrame objects
    std::string line;

    // parsing
    while (getline(input_file, line)) {
        std::istringstream ss(line);
        WiFiFrame frame;

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
        std::istringstream mcs_ss(mcs_str);
        std::string mcs_val_str;
        getline(mcs_ss, mcs_val_str, '(');
        frame.mcs.value = stoi(mcs_val_str.substr(4)); // skip "MCS=" prefix
        std::string mcs_standart_str;
        getline(mcs_ss, mcs_standart_str, ' ');
        frame.mcs.standart = mcs_standart_str.substr(0);

        size_t pos = mcs_str.find("mbps)"); // check if there's data about speed
        if (pos == -1)
        {
            frame.mcs.speed_mbps = 0;
            std::string mcs_scheme_str;
            getline(mcs_ss, mcs_scheme_str, ')');
            frame.mcs.scheme = mcs_scheme_str.substr(0);
        }
        else
        {
            std::string mcs_scheme_str;
            getline(mcs_ss, mcs_scheme_str, ' ');
            frame.mcs.scheme = mcs_scheme_str.substr(0);
            std::string mcs_speed_str;
            getline(mcs_ss, mcs_speed_str, ')');
            frame.mcs.speed_mbps = stoi(mcs_speed_str.substr(0));
        }

        std::string size_str;
        getline(ss, size_str, ',');
        frame.size = (size_t)stoi(size_str.substr(5)); // skip "Size=" prefix

        std::string bits_str;
        getline(ss, bits_str, '\n');
        frame.bits = bits_str.substr(5); // skip "Bits=" prefix

        frames.push_back(frame); // add the WiFiFrame object to the vector
    }

    input_file.close();

    return frames;
}

