//#include <iostream>
//#include <string>
//
//#include "kvs.h"
//#include "useful.h"
//#include "wav.h"
//#include "file_reader_writer.h"
//#include "index.h"
//
//using namespace std;
//
//int Index::counts = 0;
//static int sample_counts = 2000;
//
//bool unpackage_voice(const char* ksv_voice, const char* output_dir, int stride = 16);
//bool unpackage_effect(const char* header, const char* data, const char* output_dir, int stride = 16);
//bool unpackage_effect(const char* effect_file, const char* output_dir, int stride = 16);
//
//void output_music(ifstream& fin, vector<KVS>& kvs_vect, int begin_address)
//{
//	for (int a = 0, size = kvs_vect.size(); a < size; ++a)
//	{
//		ofstream fout;
//		string file_name = "./LINKSE/" + std::to_string(counts++) + ".wav";
//
//		fout.open(file_name, ios_base::binary | ios_base::out | ios_base::trunc);
//
//		output_wav_heads(fout, kvs_vect[a].get_all_size());
//		fin.seekg(begin_address + kvs_vect[a].get_begin_address(), ios::beg);
//		output_wav_body(fin, fout, kvs_vect[a].get_all_size());
//
//		fout.close();
//	}
//}
//bool output_linkse(ifstream& fin)
//{
//	const int LEN = 0x800;
//	int data = 0, head = 0;
//	vector<int> head_vect = { 0x0, 0x23800, 0x17900, 0x22e800, 0x243800, 0x25d000, 0x275800, 0x28c800,
//	0x2a8000, 0x2bf000 };
//
//	while (!fin.eof() && head < head_vect.size())
//	{
//		char p[16];
//		int cur_size = 0;
//
//		fin.read(p, 16);
//		
//		vector<int> indexs;
//		vector<KVS> music_vect;
//
//		cur_size = GET_INDEX_INT_DATA(p, 1);
//
//		indexs.push_back(GET_INDEX_INT_DATA(p, 2));
//		indexs.push_back(GET_INDEX_INT_DATA(p, 3));
//
//		get_indexs(fin, indexs);
//		get_kvs(fin, indexs.size(), music_vect);
//
//		data = head_vect[head++] + LEN;
//
//		fin.seekg(data, ios::beg);
//
//		output_music(fin, music_vect, data);
//
//		fin.seekg(head_vect[head], ios::beg);
//	}
//
//	return true;
//}
//void output_sm7_bgm()
//{
//	for (int a = 0; a <= 39; ++a)
//	{
//		if (a < 10)
//			unpackage_voice(string(SM7_INPUT_PREFER + string("B0000") + std::to_string(a) + ".bin").c_str(), SM7_BGM_OUTPUT_PREFER, 1);
//		else
//			unpackage_voice(string(SM7_INPUT_PREFER + string("B000") + std::to_string(a) + ".bin").c_str(), SM7_BGM_OUTPUT_PREFER, 1);
//	}
//	for (int a = 44; a <= 89; ++a)
//	{
//		if (a < 10)
//			unpackage_voice(string(SM7_INPUT_PREFER + string("B0000") + std::to_string(a) + ".bin").c_str(), SM7_BGM_OUTPUT_PREFER, 1);
//		else
//			unpackage_voice(string(SM7_INPUT_PREFER + string("B000") + std::to_string(a) + ".bin").c_str(), SM7_BGM_OUTPUT_PREFER, 1);
//	}
//	for (int a = 400; a <= 423; ++a)
//	{
//		unpackage_voice(string(SM7_INPUT_PREFER + string("B00") + std::to_string(a) + ".bin").c_str(), SM7_BGM_OUTPUT_PREFER, 1);
//	}
//	for (int a = 20; a <= 59; ++a)
//	{
//		unpackage_voice(string(SM7_INPUT_PREFER + string("D000") + std::to_string(a) + ".bin").c_str(), SM7_BGM_OUTPUT_PREFER, 1);
//	}
//	for (int a = 226; a <= 229; ++a)
//	{
//		unpackage_voice(string(SM7_INPUT_PREFER + string("D00") + std::to_string(a) + ".bin").c_str(), SM7_BGM_OUTPUT_PREFER, 1);
//	}
//	for (int a = 211; a <= 230; ++a)
//	{
//		unpackage_voice(string(SM7_INPUT_PREFER + string("D20") + std::to_string(a) + ".bin").c_str(), SM7_BGM_OUTPUT_PREFER, 1);
//	}
//	for (int a = 261; a <= 262; ++a)
//	{
//		unpackage_voice(string(SM7_INPUT_PREFER + string("D20") + std::to_string(a) + ".bin").c_str(), SM7_BGM_OUTPUT_PREFER, 1);
//	}
//	for (int a = 0; a <= 34; ++a)
//	{
//		if (a < 10)
//			unpackage_voice(string(SM7_INPUT_PREFER + string("H0000") + std::to_string(a) + ".bin").c_str(), SM7_BGM_OUTPUT_PREFER, 1);
//		else
//			unpackage_voice(string(SM7_INPUT_PREFER + string("H000") + std::to_string(a) + ".bin").c_str(), SM7_BGM_OUTPUT_PREFER, 1);
//	}
//	for (int a = 36; a <= 47; ++a)
//	{
//		if (a < 10)
//			unpackage_voice(string(SM7_INPUT_PREFER + string("H0000") + std::to_string(a) + ".bin").c_str(), SM7_BGM_OUTPUT_PREFER, 1);
//		else
//			unpackage_voice(string(SM7_INPUT_PREFER + string("H000") + std::to_string(a) + ".bin").c_str(), SM7_BGM_OUTPUT_PREFER, 1);
//	}
//	for (int a = 3; a <= 25; ++a)
//	{
//		if (a < 10)
//			unpackage_voice(string(SM7_INPUT_PREFER + string("J0000") + std::to_string(a) + ".bin").c_str(), SM7_BGM_OUTPUT_PREFER, 1);
//		else
//			unpackage_voice(string(SM7_INPUT_PREFER + string("J000") + std::to_string(a) + ".bin").c_str(), SM7_BGM_OUTPUT_PREFER, 1);
//	}
//	for (int a = 37; a <= 44; ++a)
//	{
//		unpackage_voice(string(SM7_INPUT_PREFER + string("J000") + std::to_string(a) + ".bin").c_str(), SM7_BGM_OUTPUT_PREFER, 1);
//	}
//	for (int a = 0; a <= 34; ++a)
//	{
//		if (a < 10)
//			unpackage_voice(string(SM7_INPUT_PREFER + string("M0000") + std::to_string(a) + ".bin").c_str(), SM7_BGM_OUTPUT_PREFER, 1);
//		else
//			unpackage_voice(string(SM7_INPUT_PREFER + string("M000") + std::to_string(a) + ".bin").c_str(), SM7_BGM_OUTPUT_PREFER, 1);
//	}
//	for (int a = 36; a <= 47; ++a)
//	{
//		if (a < 10)
//			unpackage_voice(string(SM7_INPUT_PREFER + string("M0000") + std::to_string(a) + ".bin").c_str(), SM7_BGM_OUTPUT_PREFER, 1);
//		else
//			unpackage_voice(string(SM7_INPUT_PREFER + string("M000") + std::to_string(a) + ".bin").c_str(), SM7_BGM_OUTPUT_PREFER, 1);
//	}
//}
//void output_sm8_voice()
//{
//	for (int a = 0; a <= 150; ++a)
//	{
//		if (a < 10)
//			unpackage_voice(string(string(SM8_INPUT_PREFER) + "EV00" + std::to_string(a) + STBIN_AFTER).c_str(), SM8_VOICE_OUTPUT_PREFER, 1);
//		else if (a < 100)
//			unpackage_voice(string(string(SM8_INPUT_PREFER) + "EV0" + std::to_string(a) + STBIN_AFTER).c_str(), SM8_VOICE_OUTPUT_PREFER, 1);
//		else
//			unpackage_voice(string(string(SM8_INPUT_PREFER) + "EV" + std::to_string(a) + STBIN_AFTER).c_str(), SM8_VOICE_OUTPUT_PREFER, 1);
//	}
//	vector<const char*> names = { "ADD", "BRV", "HTV", "N", "pWTV", "RV", "SCV", "SIV", "TEV", "WSIV" };
//
//	for (int a = 0, size = names.size(); a < size; ++a)
//		unpackage_voice(string(string(SM8_INPUT_PREFER) + names[a] + ASBIN_AFTER).c_str(), SM8_VOICE_OUTPUT_PREFER, 1);
//}
//
//int main()
//{
//	---- voice ----
//	SM4
//	unpackage_voice(SM4_VOICE_FILE, SM4_VOICE_OUTPUT_PREFER, 16);
//	SM5
//	unpackage_voice(SM5_VOICE_FILE, SM5_VOICE_OUTPUT_PREFER, 16);
//	SM6
//	unpackage_voice(SM6_VOICE_FILE, SM6_VOICE_OUTPUT_PREFER, 16);
//	SM7
//	for (int a = 0; a <= 3; ++a) unpackage_voice(string(SM7_INPUT_PREFER + string("LINKDATA") + std::to_string(a) + ".BIN").c_str(), SM7_VOICE_OUTPUT_PREFER, 1);
//	SM8
//	output_sm8_voice();
//	ORI
//	unpackage_voice(ORI_VOICE_FILE, ORI_VOICE_OUTPUT_PREFER, 16);
//	SMZ
//	unpackage_voice(SMZ_VOICE_FILE, SMZ_VOICE_OUTPUT_PREFER, 16);
//
//	---- bgm ----
//	SM4
//	unpackage_voice(SM4_BGM_FILE, SM4_BGM_OUTPUT_PREFER, 1);
//	SM5
//	unpackage_voice(SM5_BGM_FILE, SM5_BGM_OUTPUT_PREFER, 1);
//	SM6
//	unpackage_voice(SM6_BGM_FILE, SM6_BGM_OUTPUT_PREFER, 1);
//	SM7
//	output_sm7_bgm();
//	SM8
//	unpackage_voice(SM8_BGM_INPUT_FILE, SM8_BGM_OUTPUT_PREFER, 1);
//	ORI
//	unpackage_voice(ORI_BGM_FILE, ORI_BGM_OUTPUT_PREFER, 1);
//	SMZ
//	unpackage_voice(SMZ_BGM_FILE, SMZ_BGM_OUTPUT_PREFER, 1);
//
//
//	---- effect ----
//	ORI
//	unpackage_effect(ORI_EFFECT_FILE_HEADER, ORI_EFFECT_FILE, ORI_EFFECT_OUTPUT_PREFER);
//	SM5
//	unpackage_effect(SM5_EFFECT_FILE, SM5_EFFECT_OUTPUT_PREFER);
//	SMZ - ��SM4һ��δ����
//	unpackage_effect(SMZ_EFFECT_FILE, SMZ_EFFECT_OUTPUT_PREFER);
//
//	string header = SM4_EFFECT_OUTPUT_PREFER + string("LINKSE-") + std::to_string(179) + ".out";
//	string data = SM4_EFFECT_OUTPUT_PREFER + string("LINKSE-") + std::to_string(180) + ".out";
//
//	unpackage_effect(header.c_str(), data.c_str(), SM4_EFFECT_OUTPUT_PREFER);
//
//
//	return 0;
//}
//bool unpackage_voice(const char* kvs_voice, const char* output_dir, int stride)
//{
//	FileReader file_reader(kvs_voice);
//	FileWriter file_writer;
//	char buffer[2048];
//	int read_size;
//	static int sm5_files_counts = 0;
//
//	cout << "Begin Files Unpackage : " << kvs_voice << endl;
//
//	auto calc_buffer = [&buffer, stride](int read_size)->int
//	{
//		int index = 0;
//
//		while (index < read_size)
//		{
//			if (GET_INDEX_INT_DATA(buffer + index, 0) == KOVS)
//			{
//				return index;
//			}
//
//			index += stride;
//		}
//
//		return -1;
//	};
//	auto get_kvs_file = [&file_writer, &file_reader, &buffer, output_dir](const char* p, int before_size)->void
//	{
//		int left_size = GET_INDEX_INT_DATA(p, 1) + 16 - before_size;
//		int cur = 0;
//		int all_size = (left_size % 16 == 0 ? left_size : left_size / 16 * 16 + 16);
//
//		file_writer = output_dir + std::to_string(sm5_files_counts++) + KOVS_AFTER;
//		file_writer.write(p, before_size);
//
//		while (left_size > 0)
//		{
//			cur = (all_size >= 2048 ? file_reader.read(buffer, 2048) : file_reader.read(buffer, all_size));
//
//			if (cur == 0) return;
//
//			if (left_size < 2048)
//			{
//				file_writer.write(buffer, left_size);
//			}
//			else
//			{
//				file_writer.write(buffer, 2048);
//			}
//
//			left_size -= cur;
//			all_size -= cur;
//		}
//	};
//
//	while (read_size = file_reader.read(buffer, 2048))
//	{
//		int data_index = calc_buffer(read_size);
//
//		if (data_index == -1)
//		{
//			continue;
//		}
//
//		get_kvs_file(buffer + data_index, read_size - data_index);
//	}
//
//	return true;
//}
//bool unpackage_effect(const char* header, const char* data, const char* output_dir, int stride)
//{
//	FileReader header_reader(header), data_reader(data);
//	WavHeader wav_header;
//	vector<Index> indexs;
//	char buffer[16];
//	int read_size = 0, file_pos = 0;
//	int chunck_address = 0;
//	static int counts = 0;
//
//	auto get_indexs = [&header_reader, &indexs, &buffer](int size, int file_begin_address)-> int
//	{
//		int begin_address, all_size, i;
//		int chunck_size = 0;
//		vector<int> vect;
//
//		header_reader.seek(-12, 2);
//		header_reader.read((char*)&chunck_size, 4);
//
//		for (int a = 0; a < size; ++a)
//		{
//			header_reader.read((char*)&i, 4);
//
//			if (i != 0)
//			{
//				vect.push_back(i);
//			}
//		}
//		for (int a = 0, size = vect.size(); a < size; ++a)
//		{
//			header_reader.seek(file_begin_address + vect[a] + 20);
//			header_reader.read((char*)&begin_address, 4);
//			header_reader.read((char*)&all_size, 4);
//			indexs.push_back(move(Index(begin_address, all_size)));
//		}
//
//		return chunck_size;
//	};
//	auto output_file = [&data_reader, &wav_header](const char* output_dir, int data_size)->bool
//	{
//		FileWriter wav_writer(output_dir + std::to_string(sample_counts) + "-" + std::to_string(counts++) + ".wav");
//		int size = 0;
//		char buffer[2048];
//
//		wav_writer << wav_header;
//
//		while (data_size)
//		{
//			if (data_size >= 2048)
//				size = data_reader.read(buffer, 2048);
//			else
//				size = data_reader.read(buffer, data_size);
//
//			wav_writer.write(buffer, size);
//
//			data_size -= size;
//
//			if (size == 0) return false;
//		}
//
//		return true;
//	};
//
//	while (read_size = header_reader.read(buffer, stride))
//	{
//		if ((GET_INDEX_INT_DATA(buffer, 0) & 0x0000ffff) == 0x00003200 || (GET_INDEX_INT_DATA(buffer, 0) & 0x0000ffff) == 0x00003201)
//		{
//			indexs.clear();
//
//			int mid = get_indexs((unsigned int)(GET_INDEX_INT_DATA(buffer, 0)) >> 16, file_pos);
//
//			for (int s = 3000; s <= 13000; s += 100)
//			{
//				sample_counts = s;
//				counts = 0;
//				wav_header.set_wav_sample(s);
//				wav_header.set_wav_per_bits(8);
//				wav_header.set_wav_channel(2);
//
//				for (int a = 0, size = indexs.size(); a < size; ++a)
//				{
//					data_reader.seek(chunck_address + indexs[a].get_begin_addres());
//					wav_header.set_wav_size(indexs[a].get_size());
//
//					cout << indexs[a];
//
//					output_file(output_dir, indexs[a].get_size());
//				}
//			}
//
//			chunck_address += mid;
//
//			if (chunck_address % 0x800 != 0)
//				chunck_address = chunck_address / 0x800 * 0x800 + 0x800;
//		}
//
//		file_pos += 0x800;
//
//		header_reader.seek(file_pos);
//	}
//
//	return true;
//}
//bool unpackage_effect(const char* effect_file, const char* output_dir, int stride)
//{
//	FileReader data_reader(effect_file);
//	vector<Index> indexs;
//	WavHeader wav_header;
//	int counts = 0, size = 0;
//	int header_address, data_address;
//	char buffer[16];
//
//	wav_header.set_wav_sample(48800);
//
//	auto get_indexs = [&indexs, &data_reader](int size, int begin_address)->void
//	{
//		int cur_index, index_begin, index_size;
//		int sub = 0;
//		vector<int> vect;
//
//		for (int a = 0; a < size; ++a)
//		{
//			data_reader.read((char*)&cur_index, 4);
//
//			if (cur_index != 0)
//				vect.push_back(cur_index);
//		}
//		for (int a = 0, inner_size = vect.size(); a < inner_size; ++a)
//		{
//			data_reader.seek(begin_address + vect[a] + 16);
//			data_reader.read((char*)&sub, 4);
//			data_reader.read((char*)&index_begin, 4);
//			data_reader.read((char*)&index_size, 4);
//			indexs.push_back(move(Index(index_begin, index_size, 2 * index_size - sub)));
//		}
//	};
//	auto data_add = [](int size, int sub, char* buffer)->void
//	{
//		int index = 0;
//
//		while (index < size)
//		{
//			*(int*)(buffer + index) |= sub;
//
//			index += 4;
//		}
//	};
//	auto output_file = [&data_reader, &counts, &wav_header, &data_add](const char* output_dir, int data_size, int sub = 0)->bool
//	{
//		FileWriter wav_writer(output_dir + std::to_string(counts++) + ".wav");
//		int size = 0;
//		char buffer[2048];
//
//		wav_writer << wav_header;
//
//		while (data_size)
//		{
//			if (data_size >= 2048)
//				size = data_reader.read(buffer, 2048);
//			else
//				size = data_reader.read(buffer, data_size);
//
//			data_add(size, sub, buffer);
//
//			wav_writer.write(buffer, size);
//
//			data_size -= size;
//
//			if (size == 0) return false;
//		}
//
//		return true;
//	};
//	while (size = data_reader.read(buffer, 16))
//	{
//		if (GET_INDEX_INT_DATA(buffer, 0) == HBW)
//		{
//			indexs.clear();
//
//			header_address = data_reader.pos() - 4;
//			data_reader.seek(4, 2);
//
//			get_indexs(GET_INDEX_INT_DATA(buffer, 3) >> 16, header_address);
//
//			if (data_reader.pos() % 16 != 0)
//				data_reader.seek(16 - data_reader.pos() % 16, 2);
//		}
//		else if (GET_INDEX_INT_DATA(buffer, 0) == DBW)
//		{
//			data_reader.seek(-4, 2);
//
//			data_address = data_reader.pos();
//
//			for (int a = 0, size = indexs.size(); a < size; ++a)
//			{
//				data_reader.seek(data_address + indexs[a].get_begin_addres());
//				wav_header.set_wav_size(indexs[a].get_size());
//
//				output_file(output_dir, indexs[a].get_size(), indexs[a].get_sub());
//			}
//
//			if (data_reader.pos() % 16 != 0)
//				data_reader.seek(16 - data_reader.pos() % 16, 2);
//		}
//	}
//
//	return true;
//}