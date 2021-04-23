#include <iostream>
#include <vector>

#include "wav.h"

using namespace std;

vector<unsigned int> WavHeader::wav_header_info =
{
	0x46464952, 0, 0x45564157, 0x20746d66, 0x10,
	0x010001, 0xbb80, 0x017700, 0x100002, 0x61746164,
	0
};
WavHeader::WavHeader(int size, int channel, int sample, int sample_bits)
{
	wav_header_info[5] = (wav_header_info[5] & 0xffff) + (channel << 16);
	wav_header_info[6] = sample;
	wav_header_info[8] = (sample_bits << 16) + (wav_header_info[5] >> 16) * (wav_header_info[8] >> 16) / 8;
	wav_header_info[7] = wav_header_info[6] * (wav_header_info[5] >> 16) * (wav_header_info[8] >> 16) / 8;

	wav_header_info[1] = size + 36;
	wav_header_info[10] = size;
}