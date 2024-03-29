#include "WiFiFrame.h"

WiFiFrame::WiFiFrame()
{
	id = 0;
	offset = 0.0;
	bandWidth = 0;
	mcs = 0;
	modulation = "";
	size = 0;
	bits = "";
}

WiFiFrame::WiFiFrame(uint32_t Id, float Offset, uint16_t BandWidth, uint16_t Mcs, std::string Modulation, uint32_t Size, std::string Bits)
{
	id = Id;
	offset = Offset;
	bandWidth = BandWidth;
	mcs = Mcs;
	modulation = Modulation;
	size = Size;
	bits = Bits;
}

WiFiFrame::~WiFiFrame()
{
}

std::pair<std::vector<WiFiFrame>, uint32_t> WiFiFrame::parse(const std::string fileName)
{
	std::vector<WiFiFrame> frames;
	uint32_t error = 0;

	std::ifstream input_file(fileName);
	if (!input_file.is_open())
		error = -1;

	std::string line;
	
	uint32_t lineCount = 0;
	// parsing
	while (error == 0 && getline(input_file, line))
	{
		lineCount++;
		std::istringstream ss(line);
		WiFiFrame frame;

		std::string id_str;
		getline(ss, id_str, '\t');
		if (isNumeric(id_str))
			frame.id = static_cast<uint32_t>(stoi(id_str));
			
		else {
			error = lineCount;
			break;
		}

		std::string offset_str;
		getline(ss, offset_str, ',');
		if (offset_str.substr(0, 7) == "Offset=")
		{
			offset_str = offset_str.substr(7); // skip "Offset=" prefix
			if(isNumeric(offset_str))
				frame.offset = stof(offset_str); 
			else {
				error = lineCount;
				break;
			}
		}
		else {
			error = lineCount;
			break;
		}

		std::string bw_str;
		getline(ss, bw_str, 'M');
		if (bw_str.substr(0, 3) == "BW=")
		{
			bw_str = bw_str.substr(3); // skip "BW=" prefix
			if(isNumeric(bw_str))
				frame.bandWidth = static_cast<uint8_t>(stoi(bw_str)); 
			else {
				error = lineCount;
				break;
			}
		}	
		else {
			error = lineCount;
			break;
		}
		
		ss.ignore(3); // hz,

		std::string mcs_str;
		getline(ss, mcs_str, '(');
		if (mcs_str.substr(0, 4) == "MCS=")
		{
			mcs_str = mcs_str.substr(4);
			if (isNumeric(mcs_str))
				frame.mcs = static_cast<uint8_t>(stoi(mcs_str));
			else {
				error = lineCount;
				break;
			}
		}
		else {
			error = lineCount;
			break;
		}
		
		std::string mod_str;
		getline(ss, mod_str, ')');
		if (mod_str.substr(0, 6) == "802.11")
			frame.modulation = mod_str; 
		else {
			error = lineCount;
			break;
		}

		ss.ignore(1); // , after )

		std::string size_str;
		getline(ss, size_str, ',');
		if (size_str.substr(0, 5) == "Size=")
		{
			size_str = size_str.substr(5); // skip "Size=" prefix
			if (isNumeric(size_str))
				frame.size = static_cast<uint32_t>(stoi(size_str));
			else {
				error = lineCount;
				break;
			}
		}
		else {
			error = lineCount;
			break;
		}
		std::string bits_str;
		getline(ss, bits_str, '\n');
		if (bits_str.substr(0, 5) == "Bits=")
			frame.bits = bits_str.substr(5); // skip "Bits=" prefix
		else {
			error = lineCount;
			break;
		}

		frames.push_back(frame); // add a WiFiFrame object to the vector
	}
	input_file.close();
	if (error)
	{
		frames.clear();
		frames.shrink_to_fit();
	}
	return { frames, error };
}

uint8_t* WiFiFrame::dataToByteArray(const std::string hexStr, std::size_t size)
{
	uint8_t* byteArray = new uint8_t[size];
	for (size_t i = 0; i < size * 2; i += 2) // hex string to byte array
	{
		std::string byteString = hexStr.substr(i, 2);
		byteArray[i / 2] = static_cast<uint8_t>(std::stoi(byteString, nullptr, 16));
	}
	return byteArray;
}

std::string WiFiFrame::hexToBinary(const std::string& hex)
{
	std::stringstream ss;
	for (size_t i = 0; i < hex.length(); ++i) 
	{
		uint8_t byte = std::stoi(hex.substr(i, 2), nullptr, 16);
		ss << std::bitset<8>(byte);
	}
	return ss.str();
}

// CRC polynomial 0xedb88320
static const uint32_t crc_32_tab[] = { 
	0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f,
	0xe963a535, 0x9e6495a3, 0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
	0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2,
	0xf3b97148, 0x84be41de, 0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
	0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9,
	0xfa0f3d63, 0x8d080df5, 0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
	0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b, 0x35b5a8fa, 0x42b2986c,
	0xdbbbc9d6, 0xacbcf940, 0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
	0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423,
	0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
	0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d, 0x76dc4190, 0x01db7106,
	0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
	0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d,
	0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
	0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
	0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
	0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7,
	0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
	0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa,
	0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
	0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,
	0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
	0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84,
	0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
	0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
	0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
	0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,
	0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
	0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55,
	0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
	0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28,
	0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
	0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,
	0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
	0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
	0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
	0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69,
	0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
	0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc,
	0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
	0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693,
	0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
	0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};

uint32_t WiFiFrame::calculateCRC32( const uint8_t* data, std::size_t size )
{
	uint32_t crc = 0xffffffff;
	for (; size; --size, ++data) {
		crc = (crc >> 8) ^ crc_32_tab[(crc ^ *data) & 0xff];
	}

	return crc ^ 0xffffffff;
}

bool WiFiFrame::checkCRC32(const std::string hexStr, std::size_t size)
{
	uint8_t* byteArray = dataToByteArray(hexStr, size);
	const uint32_t actualChecksum = *reinterpret_cast<const uint32_t*>(byteArray + size - 4);
	uint32_t calcChecksum = calculateCRC32(byteArray, size - 4);
	delete[] byteArray;
	
	return actualChecksum == calcChecksum;
}

short int WiFiFrame::getType()
{
	// (stoi(bits.substr(0, 2), nullptr, 16)) - the first FC byte
	short int type = ((stoi(bits.substr(0, 2), nullptr, 16)) & 0b00001100) >> 2;
	return type;
}

bool WiFiFrame::isBeacon()
{
	// (stoi(bits.substr(0, 2), nullptr, 16)) - the first FC byte
	short int subtype = ((stoi(bits.substr(0, 2), nullptr, 16)) & 0b11110000) >> 4;
	if (subtype == 0b1000)
		return true;
	return false;
}

std::string WiFiFrame::getBeaconSSID()
{
	const int offset = 37 * 2; // 36 bytes before SSID information + 1 id byte before size
	uint8_t size = (stoi(bits.substr(offset, 2), nullptr, 16));
	std::string ssidHex = bits.substr(offset + 2, size * 2); // skipping 1 more byte right to SSID
	std::string asciiString = "";
	//hex to ASCII
	for (size_t i = 0; i < size * 2; i += 2) {
		unsigned int asciiValue = std::stoul(ssidHex.substr(i, 2), nullptr, 16);
		asciiString += static_cast<char>(asciiValue);
	}
	return asciiString;
}

bool WiFiFrame::compareSSID(std::string SSID) // checks if SSID matches the given pattern
{
	const std::string pattern = "Drone4";
	if(SSID.length() < pattern.length())
		return false;

	return SSID.substr(0, pattern.length()) == pattern;
}

std::string WiFiFrame::getSA()
{
	const int offset = 10 * 2;
	std::string sourceAddress = bits.substr(offset, 6 * 2);
	return sourceAddress;
}

WiFiFrame::ProcessingResult WiFiFrame::processing(std::vector <WiFiFrame> data)
{
	std::vector<WiFiFrame> drone_frames; // return vector
	WiFiFrame::ProcessingResult result;
	std::vector<WiFiFrame> frames_sorted;
	std::vector<WiFiFrame> data_frames; // a vector to hold data frames for the last task

	for (size_t i = 0; i < data.size(); i++)
	{
		if (WiFiFrame::checkCRC32(data[i].bits, data[i].size))
			frames_sorted.push_back(data[i]);
	}

	data.clear();
	data.shrink_to_fit();

	for (size_t i = 0; i < frames_sorted.size(); i++)
	{
		if (frames_sorted[i].getType() == 0)
		{
			if (frames_sorted[i].isBeacon())
			{
				std::string SSID = frames_sorted[i].getBeaconSSID();
				if (WiFiFrame::compareSSID(SSID))
				{
						result.MAC = frames_sorted[i].getSA();
						result.SSID = SSID;
				}
			}
		}
		if (frames_sorted[i].getType() == 2)
			data_frames.push_back(frames_sorted[i]);
	}

	frames_sorted.clear();
	frames_sorted.shrink_to_fit();

	for (size_t i = 0; i < data_frames.size(); i++)
	{
		if (result.MAC == data_frames[i].getSA())
		{
			drone_frames.push_back(data_frames[i]);
		}
	}

	data_frames.clear();
	data_frames.shrink_to_fit();

	result.droneFrames = drone_frames; 
	return result;
}

void WiFiFrame::writeToFile(std::vector <WiFiFrame>& drone_frames, const std::string fileName)
{
	std::ofstream outputFile(fileName);

	if (outputFile.is_open()) {
		for (size_t i = 0; i < drone_frames.size(); i++)
		{
			outputFile << std::setfill('0') << std::setw(10) << drone_frames[i].id << "\t"
				<< "Offset=" << drone_frames[i].offset << ","
				<< "BW=" << drone_frames[i].bandWidth << "MHz,"
				<< "MCS=" << drone_frames[i].mcs << "(" 
				<< drone_frames[i].modulation << ")," 
				<< "Size=" << drone_frames[i].size << ","
				<< "Bits=" << drone_frames[i].bits << std::endl;
		}
	}
	else {
		std::cout << "Error: Failed to open the output file." << std::endl;
	}
	outputFile.close();
}

