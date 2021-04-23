#include <iostream>
#include <filesystem>

#include "file_reader_writer.h"

using namespace std;

//---------FileReader
FileReader::FileReader(const string& file)
{
	file_name = file;

	reader.open(file_name, ios_base::in | ios_base::binary);

	if (reader.is_open())
	{
		set_flag(READERINFO::OPENNING);
	}
	else 
	{
		set_flag(READERINFO::NOFILES);
	}

	cout << get_info() << endl;
}
FileReader::~FileReader()
{
	if (reader.is_open())
	{
		reader.close();
	}

	cout << get_info() << endl;
}
void FileReader::set_info()
{
	READERINFO info = (READERINFO)get_flag();

	switch (info)
	{
	case READERINFO::NOFILES:
		Message::set_info(move("File : " + file_name + " Not Exits!!!"));
		break;
	case READERINFO::OPENNING:
		Message::set_info(move("File : " + file_name + " Is Openning, Begin To Solve!!!"));
		break;
	case READERINFO::SUCCESSFUL:
		Message::set_info(move("File : " + file_name + " Solve Successful!!!"));
		break;
	default:
		Message::set_info(move("File : " + file_name + " Something Dont't Know!!!"));
		break;
	}
}
int FileReader::read(char* p, int len)
{
	if (!reader.is_open())
	{
		return -1;
	}

	reader.read(p, len);

	return reader.gcount();
}
void FileReader::seek(int pos, Seek s)
{
	switch (s)
	{
	case Seek::BEGIN:
		reader.seekg(pos, ios::beg);
		break;
	case Seek::CURRENT:
		reader.seekg(pos, ios::cur);
		break;
	case Seek::END:
		reader.seekg(pos, ios::end);
		break;
	}
}

//--------------FileWriter
FileWriter::FileWriter(const string& file)
{
	file_name = file;

	writer.open(file_name, ios::out | ios::binary | ios::trunc);

	if (writer.is_open())
	{
		set_flag(WRITERINFO::OPENNING);
	}
	else
	{
		string direct = file_name.substr(0, file_name.find_last_of("/"));

		if (filesystem::create_directories(direct))
		{
			set_flag(WRITERINFO::DIRECTSSUCCESSFUL);
		}
		else
		{
			set_flag(WRITERINFO::DIRECTFAIL);
		}

		writer.open(file_name, ios::out | ios::binary | ios::trunc);

		if (writer.is_open())
		{
			set_flag(WRITERINFO::OPENNING);
		}
		else
		{
			set_flag(WRITERINFO::FAIL);
		}
	}
}
FileWriter::~FileWriter()
{
	if (writer.is_open())
	{
		writer.close();
	}
}
void FileWriter::set_info()
{
	WRITERINFO info = (WRITERINFO)get_flag();

	switch (info)
	{
	case WRITERINFO::DIRECTFAIL:
		Message::set_info(move("Direct : " + file_name + " Not Exits!!!"));
		break;
	case WRITERINFO::DIRECTSSUCCESSFUL:
		Message::set_info(move("Direct : " + file_name + " Create Successful!!!"));
		break;
	case WRITERINFO::FAIL:
		Message::set_info(move("File : " + file_name + " Write Fail!!!"));
		break;
	case WRITERINFO::OPENNING:
		Message::set_info(move("File : " + file_name + " Is Openning, Begin To Solve!!!"));
		break;
	case WRITERINFO::SUCCESSFUL:
		Message::set_info(move("File : " + file_name + " Solve Successful!!!"));
		break;
	default:
		Message::set_info(move("File : " + file_name + " Something Dont't Know!!!"));
		break;
	}
}
bool FileWriter::write(const char* p, int len)
{
	if (!writer.is_open())
	{
		return false;
	}

	writer.write(p, len);

	return true;
}