#ifndef __WAV_H
#define __WAV_H

#include <iostream>
#include <vector>

#include "file_reader_writer.h"

using namespace std;

class WavHeader
{
private:
	static vector<unsigned int> wav_header_info;
	//0x46464952, len + 36, 0x45564157, 0x20746d66, 0x10
	//0x010001, 0x5622, 0xac44, 0x100002, 0x61746164
	//size

public:
	WavHeader(int size, int channel = 1, int sample = 22050, int sample_bits = 16);

public:
	friend FileWriter& operator<<(FileWriter& writer, const WavHeader& wav_header)
	{
		writer.write(reinterpret_cast<const char*>(&(wav_header.wav_header_info[0])), sizeof(unsigned int) * wav_header.wav_header_info.size());

		return writer;
	}
};

#endif