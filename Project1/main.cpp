#include <iostream>
#include <string>
#include <io.h>

#include "kvs.h"
#include "useful.h"
#include "wav.h"
#include "file_reader_writer.h"
#include "index.h"

using namespace std;

int Index::counts = 0;
static int sample_counts = 2000;
static int kvs_counts = 0;
static int effect_counts = 0;
static char buffer[2048];

//Voice BGM
int calc_buffer(int read_size, int flag, int stride);
bool get_kvs_file(FileReader& reader, const string& output_dir, int index, int before_size);
bool unpackage_kvs(const string& ksv_voice, const string& output_dir, int stride);
bool unpackage_more_kvs(const vector<string>& vect, const string& output_dir, int stride);

//Effect
int get_indexs(FileReader& reader, vector<Index>& indexs, int& begin_address);
bool get_effect_file(FileReader& reader, const string& output_dir, int size);
bool unpackage_effect_file(FileReader& reader, const string& output_dir, vector<Index>& indexs, int chunck_address);
bool unpackage_effect(const string& header, const string& output_dir, int stride);
bool unpackage_effect_with_header(const string& header, const string& data, const string& output_dir, int stride);

//Others
void get_files(string path, vector<string>& files);

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

void get_files_name(vector<string>& files, int begin, int end, const char* prefer, const char* mid, const char* after)
{
	for (; begin <= end; ++begin)
	{
		files.push_back(string(prefer) + mid + std::to_string(begin) + after);
	}
}
//VOICE
void sm4_voice()
{
	kvs_counts = 0;

	unpackage_more_kvs({ string(SM4_INPUT_PREFER) + SM4_VOICE_FILE }, SM4_VOICE_OUTPUT_PREFER, 16);
}
void sm5_voice()
{
	kvs_counts = 0;

	unpackage_more_kvs({ string(SM5_INPUT_PREFER) + SM5_VOICE_FILE }, SM5_VOICE_OUTPUT_PREFER, 16);
}
void sm6_voice()
{
	kvs_counts = 0;

	unpackage_more_kvs({ string(SM6_INPUT_PREFER) + SM6_VOICE_FILE }, SM6_VOICE_OUTPUT_PREFER, 16);
}
void sm7_voice()
{
	vector<string> files;

	kvs_counts = 0;

	get_files_name(files, 0, 3, SM7_INPUT_PREFER, "LINKDATA", ".BIN");
	unpackage_more_kvs(files, SM7_VOICE_OUTPUT_PREFER, 1);
}
void sm7e_voice()
{
	kvs_counts = 0;

	unpackage_more_kvs({ string(SM7E_INPUT_PREFER) + SM7E_VOICE_FILE }, SM7E_VOICE_OUTPUT_PREFER, 1);
}
void sm8_voice()
{
	vector<string> files;
	vector<string> names = { "ADD", "BRV", "HTV", "N", "pWTV", "RV", "SCV", "SIV", "TEV", "WSIV" };

	kvs_counts = 0;

	//get_files_name(files, 0, 9, SM8_INPUT_PREFER, "EV00", STBIN_AFTER);
	//get_files_name(files, 10, 99, SM8_INPUT_PREFER, "EV0", STBIN_AFTER);
	//get_files_name(files, 100, 150, SM8_INPUT_PREFER, "EV", STBIN_AFTER);

	for (int a = 0, size = names.size(); a < size; ++a)
	{
		files.push_back(SM8_INPUT_PREFER + names[a] + ASBIN_AFTER);
	}

	unpackage_more_kvs(files, SM8_VOICE_OUTPUT_PREFER, 1);
}
void ori_voice()
{
	kvs_counts = 0;

	unpackage_more_kvs({ string(ORI_INPUT_PREFER) + ORI_VOICE_FILE }, ORI_VOICE_OUTPUT_PREFER, 16);
}
void smz_voice()
{
	kvs_counts = 0;

	unpackage_more_kvs({ string(SMZ_INPUT_PREFER) + SMZ_VOICE_FILE }, SMZ_VOICE_OUTPUT_PREFER, 16);
}
void smol_voice()
{
	long hfile = 0;
	vector<string> files;
	_finddata_t fileinfo;

	get_files(SMOL_INPUT_PREFER, files);

	unpackage_more_kvs(files, SMOL_VOICE_OUTPUT_PREFER, 1);
}
void sr2_voice()
{
	kvs_counts = 0;

	unpackage_more_kvs({ string(SR2_INPUT_PREFER) + SR2_VOICE_FILE }, SR2_VOICE_OUTPUT_PREFER, 16);
}

//BGM
void sm4_bgm()
{
	kvs_counts = 0;

	unpackage_more_kvs({ string(SM4_INPUT_PREFER) + SM4_BGM_FILE }, SM4_BGM_OUTPUT_PREFER, 1);
}
void sm5_bgm()
{
	kvs_counts = 0;

	unpackage_more_kvs({ string(SM5_INPUT_PREFER) + SM5_BGM_FILE }, SM5_BGM_OUTPUT_PREFER, 1);
}
void sm6_bgm()
{
	kvs_counts = 0;

	unpackage_more_kvs({ string(SM6_INPUT_PREFER) + SM6_BGM_FILE }, SM6_BGM_OUTPUT_PREFER, 1);
}
void sm7_bgm()
{
	vector<string> files;

	kvs_counts = 0;

	get_files_name(files, 0, 9, SM7_INPUT_PREFER, "B0000", ".bin");
	get_files_name(files, 10, 39, SM7_INPUT_PREFER, "B000", ".bin");
	get_files_name(files, 44, 89, SM7_INPUT_PREFER, "B000", ".bin");
	get_files_name(files, 400, 423, SM7_INPUT_PREFER, "B00", ".bin");
	get_files_name(files, 20, 59, SM7_INPUT_PREFER, "D000", ".bin");
	get_files_name(files, 226, 229, SM7_INPUT_PREFER, "D00", ".bin");
	get_files_name(files, 211, 230, SM7_INPUT_PREFER, "D20", ".bin");
	get_files_name(files, 261, 262, SM7_INPUT_PREFER, "D20", ".bin");
	get_files_name(files, 0, 9, SM7_INPUT_PREFER, "H0000", ".bin");
	get_files_name(files, 10, 34, SM7_INPUT_PREFER, "H000", ".bin");
	get_files_name(files, 36, 47, SM7_INPUT_PREFER, "H000", ".bin");
	get_files_name(files, 3, 9, SM7_INPUT_PREFER, "J0000", ".bin");
	get_files_name(files, 10, 25, SM7_INPUT_PREFER, "J000", ".bin");
	get_files_name(files, 37, 44, SM7_INPUT_PREFER, "J000", ".bin");
	get_files_name(files, 0, 9, SM7_INPUT_PREFER, "M0000", ".bin");
	get_files_name(files, 10, 34, SM7_INPUT_PREFER, "M000", ".bin");
	get_files_name(files, 36, 47, SM7_INPUT_PREFER, "M000", ".bin");

	unpackage_more_kvs(files, SM7_BGM_OUTPUT_PREFER, 1);
}
void sm7e_bgm()
{
	kvs_counts = 0;

	unpackage_more_kvs({ string(SM7E_INPUT_PREFER) + SM7E_BGM_FILE }, SM7E_BGM_OUTPUT_PREFER, 1);
}
void sm8_bgm()
{
	kvs_counts = 0;

	unpackage_more_kvs({ string(SM8_INPUT_PREFER) + SM8_BGM_FILE }, SM8_BGM_OUTPUT_PREFER, 1);
}
void ori_bgm()
{
	kvs_counts = 0;

	unpackage_more_kvs({ string(ORI_INPUT_PREFER) + ORI_BGM_FILE }, ORI_BGM_OUTPUT_PREFER, 1);
}
void smz_bgm()
{
	kvs_counts = 0;

	unpackage_more_kvs({ string(SMZ_INPUT_PREFER) + SMZ_BGM_FILE }, SMZ_BGM_OUTPUT_PREFER, 1);
}
void sr2_bgm()
{
	kvs_counts = 0;

	unpackage_more_kvs({ string(SR2_INPUT_PREFER) + SR2_BGM_FILE }, SR2_BGM_OUTPUT_PREFER, 1);
}

//EFFECT
void ori_effect()
{
	effect_counts = 0;

	unpackage_effect_with_header(string(ORI_INPUT_PREFER) + ORI_EFFECT_FILE_HEADER, string(ORI_INPUT_PREFER) + ORI_EFFECT_FILE, ORI_EFFECT_OUTPUT_PREFER, 16);
}
void sm4_effect()
{
	effect_counts = 0;

	unpackage_effect_with_header(string(SM4_INPUT_PREFER) + "LINKSE-" + std::to_string(139) + ".out",
		string(SM4_INPUT_PREFER) + "LINKSE-" + std::to_string(140) + ".out", SM4_EFFECT_OUTPUT_PREFER, 1);
}
void sm5_effect()
{
	effect_counts = 0;

	unpackage_effect(string(SM5_INPUT_PREFER) + SM5_EFFECT_FILE, SM5_EFFECT_OUTPUT_PREFER, 1);
}
void smz_effect()
{
	effect_counts = 0;

	unpackage_effect(string(SMZ_INPUT_PREFER) + SMZ_EFFECT_FILE, SMZ_EFFECT_OUTPUT_PREFER, 1);
}
void sr2_effect()
{
	effect_counts = 0;

	unpackage_effect_with_header(string(SR2_INPUT_PREFER) + SR2_EFFECT_FILE_HEADRE, string(SR2_INPUT_PREFER) + SR2_EFFECT_FILE, SR2_EFFECT_OUTPUT_PREFER, 16);
}

int main()
{
	//---- voice ----
	//SM4
	//sm4_voice();
	//SM5
	//sm5_voice();
	//SM6
	//sm6_voice();
	//SM7
	//sm7_voice();
	//SM7E
	sm7e_voice();
	//SM8
	//sm8_voice();
	//ORI
	//ori_voice();
	//SMZ
	//smz_voice();
	//SMOL
	//smol_voice();
	//SR2
	//sr2_voice();
	
	//---- bgm ----
	//SM4
	//sm4_bgm();
	//SM5
	//sm5_bgm();
	//SM6
	//sm6_bgm();
	//SM7
	//sm7_bgm();
	//SM7E
	sm7e_bgm();
	//SM8
	//sm8_bgm();
	//ORI
	//ori_bgm();
	//SMZ
	//smz_bgm();
	//SMOL
	//smol_voice();
	//SR2
	//sr2_bgm();
	
	//---- effect ----
	//ORI
	//ori_effect();
	//SM4
	//sm4_effect();
	//SM5
	//sm5_effect();
	//SM6
	//sm6_effect();
	//unpackage_effect(SM5_EFFECT_FILE, SM5_EFFECT_OUTPUT_PREFER);
	//SMZ - 跟SM4一样未解决
	//unpackage_effect(SMZ_EFFECT_FILE, SMZ_EFFECT_OUTPUT_PREFER);
	//SMZ
	//smz_effect();
	//SR2
	//sr2_effect();

	return 0;
}
int calc_buffer(int read_size, int flag, int stride)
{
	int index = 0;

	while (index < read_size)
	{
		if (GET_INDEX_INT_DATA(buffer + index, 0) == flag)
		{
			return index;
		}

		index += stride;
	}
	
	return -1;
}
//----------------Unpackage Voice BGM
bool get_kvs_file(FileReader& reader, const string& output_dir, int index, int before_size)
{
	int left_size = GET_INDEX_INT_DATA(buffer + index, 1) + 16 - before_size;
	int all_size = (left_size % 16 == 0 ? left_size : left_size / 16 * 16 + 16);
	int cur = 0;

	FileWriter writer(output_dir + std::to_string(kvs_counts++) + KOVS_AFTER);

	if (writer.get_flag() == FileWriter::WRITERINFO::DIRECTFAIL)
	{
		cout << writer.get_info() << endl;

		return false;
	}

	writer.write(buffer + index, before_size);

	while (left_size > 0)
	{
		cur = (all_size >= 2048 ? reader.read(buffer, 2048) : reader.read(buffer, all_size));

		if (cur == 0)
		{
			writer.set_flag(FileWriter::WRITERINFO::FAIL);

			cout << writer.get_info() << endl;

			return false;
		}

		if (left_size < 2048)
		{
			writer.write(buffer, left_size);
		}
		else
		{
			writer.write(buffer, 2048);
		}

		left_size -= cur;
		all_size -= cur;
	}

	return true;
}
bool unpackage_kvs(const string& kvs_voice, const string& output_dir, int stride)
{
	FileReader reader(kvs_voice);
	int read_size;

	if (reader.get_flag() == FileReader::READERINFO::NOFILES)
	{
		return false;
	}

	reader.set_flag(FileReader::READERINFO::OPENNING);

	while (read_size = reader.read(buffer, 2048))
	{
		int index = calc_buffer(read_size, KOVS, stride);

		if (index != -1)
		{
			get_kvs_file(reader, output_dir, index, read_size - index);
		}
	}

	reader.set_flag(FileReader::READERINFO::SUCCESSFUL);

	return true;
}
bool unpackage_more_kvs(const vector<string>& vect, const string& output_dir, int stride)
{
	for (int a = 0, size = vect.size(); a < size; ++a)
	{
		unpackage_kvs(vect[a], output_dir, stride);
	}

	return true;
}

//----------------Unpackage Effect Without Header
int get_indexs(FileReader& reader, vector<Index>& indexs, int& header_size)
{
	vector<int> vect;
	int index_size, i;
	int chunck_size = 0, begin_address = reader.pos();

	reader.read((char*)&index_size, 4);
	reader.read((char*)&chunck_size, 4);

	index_size >>= 16;
	header_size = index_size * 44 + 8;

	for (int a = 0; a < index_size; ++a)
	{
		reader.read((char*)&i, 4);

		if (i != 0)
		{
			vect.push_back(i);
		}
	}

	index_size = vect.size();

	int dbw_begin_address = 0;
	int dbw_index_begin_address, dbw_index_all_size;

	for (int a = 0; a < index_size; ++a)
	{
		dbw_begin_address = vect[a] + begin_address;

		reader.seek(dbw_begin_address - reader.pos() + 20, FileReader::Seek::CURRENT);

		reader.read((char*)&dbw_index_begin_address, 4);
		reader.read((char*)&dbw_index_all_size, 4);

		indexs.push_back(move(Index(dbw_index_begin_address, dbw_index_all_size)));
	}

	reader.seek(begin_address - reader.pos(), FileReader::Seek::CURRENT);

	return chunck_size;
}
bool get_effect_file(FileReader& reader, const string& output_dir, int size)
{
	FileWriter writer(output_dir + std::to_string(effect_counts++) + WAV_AFTER);
	WavHeader header(size);
	int cur = 0;

	if (writer.get_flag() == FileWriter::WRITERINFO::DIRECTFAIL)
	{
		cout << writer.get_info() << endl;

		return false;
	}

	writer << header;

	while (cur = (size >= 2048 ? reader.read(buffer, 2048) : reader.read(buffer, size)))
	{
		if (cur == 0)
		{
			writer.set_flag(FileWriter::WRITERINFO::FAIL);

			cout << writer.get_info() << endl;

			return false;
		}

		writer.write(buffer, cur);

		size -= cur;
	}

	return true;
}
bool unpackage_effect_file(FileReader& reader, const string& output_dir, vector<Index>& indexs, int chunck_address)
{
	reader.seek(chunck_address, FileReader::Seek::BEGIN);

	for (int a = 0, len = indexs.size(); a < len; ++a)
	{
		reader.seek(chunck_address + indexs[a].get_begin_addres() - reader.pos(), FileReader::Seek::CURRENT);

		get_effect_file(reader, output_dir, indexs[a].get_size());
	}

	return true;
};
bool unpackage_effect(const string& header, const string& output_dir, int stride)
{
	FileReader reader(header);
	vector<Index> indexs;
	int read_size, header_size = 0;
	bool change = true;

	if (reader.get_flag() == FileReader::READERINFO::NOFILES)
	{
		return false;
	}

	while (read_size = reader.read(buffer, 2048))
	{
		int index = (change ? calc_buffer(read_size, HBW, stride) : calc_buffer(read_size, DBW, stride));

		if (index != -1)
		{
			if (change)
			{
				indexs.clear();

				reader.seek(reader.pos() - read_size + index + 12, FileReader::Seek::BEGIN);
				
				get_indexs(reader, indexs, header_size);
			}
			else
			{
				unpackage_effect_file(reader, output_dir, indexs, reader.pos() - read_size + index + 12);
			}

			change = !change;
		}
	}
	
	reader.set_flag(FileReader::READERINFO::SUCCESSFUL);

	return true;
}

//----------------Unpackage Effect With Header
int get_reader_indexs(FileReader& reader, vector<Index>& indexs, vector<int>& header_info)
{
	int all_size = header_info[0] * 44 + 8;
	int mid;

	all_size = BYTE_ALIGNMENT(all_size, 2048);

	vector<char> solve_buffer(all_size);

	int read_size = reader.read(&solve_buffer[0], all_size - 8);

	for (int a = 0; a < header_info[0]; ++a)
	{
		mid = GET_INDEX_INT_DATA(&solve_buffer[0], a);

		if (mid != 0)
		{
			indexs.push_back(Index(GET_INDEX_INT_DATA(&solve_buffer[0] + mid + 12, 0),
				GET_INDEX_INT_DATA(&solve_buffer[0] + mid + 16, 0)));
		}
	}

	return read_size;
}
bool unpackage_effect_with_header(const string& header, const string& data, const string& output_dir, int stride)
{
	FileReader header_reader(header), data_reader(data);
	vector<Index> indexs;
	vector<int> header_info(2, 0);
	int chunck_size = 0;

	if (header_reader.get_flag() == FileReader::READERINFO::NOFILES || data_reader.get_flag() == FileReader::READERINFO::NOFILES)
	{
		return false;
	}

	auto get_header_size_indexs = [](FileReader& reader, vector<int>& vect)->bool
	{
		reader.read((char*)&vect[0], 4);
		reader.read((char*)&vect[1], 4);

		vect[0] >>= 16;

		return reader.get_eof();
	};

	while (!get_header_size_indexs(header_reader, header_info))
	{
		indexs.clear();

		get_reader_indexs(header_reader, indexs, header_info);
		unpackage_effect_file(data_reader, output_dir, indexs, chunck_size);

		chunck_size = BYTE_ALIGNMENT(chunck_size + header_info[1], 2048);
	}

	header_reader.set_flag(FileReader::READERINFO::SUCCESSFUL);
	data_reader.set_flag(FileReader::READERINFO::SUCCESSFUL);

	return true;
}
void get_files(string path, vector<string>& files)
{
	long hfile = 0;
	_finddata_t fileinfo;

	if ((hfile = _findfirst(string(path).append("*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if (fileinfo.attrib & _A_SUBDIR)
			{
				if (fileinfo.name != string(".") && fileinfo.name != string(".."))
					get_files(path + fileinfo.name + "/", files);
			}
			else
			{
				files.push_back(path + fileinfo.name);
			}
		} while (_findnext(hfile, &fileinfo) == 0);

		_findclose(hfile);
	}
}