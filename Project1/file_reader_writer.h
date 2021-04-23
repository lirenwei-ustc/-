#ifndef __FILE_READER_WRITER_H
#define __FILE_READER_WRITER_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Message
{
private:
	int flag;
	string info;

protected:
	virtual void set_info() = 0;

protected:
	inline void set_flag(int f)
	{
		flag = f;
	}
	inline int get_flag()
	{
		return flag;
	}
	inline void set_info(string& i)
	{
		info = i;
	}
	inline void set_info(string&& i)
	{
		info = i;
	}

public:
	inline string& get_info()
	{
		return info;
	}
};
class FileMessage : public Message
{
public:
	enum class READERINFO
	{
		NOFILES = -1, SUCCESSFUL, OPENNING
	};
	enum class WRITERINFO
	{
		DIRECTFAIL = -1, DIRECTSSUCCESSFUL, SUCCESSFUL, OPENNING, FAIL
	};

public:
	virtual void set_info() = 0;
};
class FileReader : public FileMessage
{
private:
	ifstream reader;
	string file_name;

public:
	enum class Seek
	{
		CURRENT, BEGIN, END
	};

public:
	FileReader(const string& file);
	~FileReader();

public:
	virtual void set_info();

public:
	inline int pos()
	{
		return reader.tellg();
	}
	inline void set_flag(READERINFO i)
	{
		Message::set_flag((int)i);
		set_info();
	}
	inline READERINFO get_flag()
	{
		return (READERINFO)Message::get_flag();
	}
	inline bool get_eof()
	{
		return reader.eof();
	}

public:
	int read(char* p, int len);
	void seek(int pos, Seek s);
};

class FileWriter : public FileMessage
{
private:
	ofstream writer;
	string file_name;

public:
	FileWriter(const string& file);
	~FileWriter();

public:
	const char* operator=(const char* file_name)
	{
		if (writer.is_open())
		{
			writer.close();
		}

		writer.open(file_name, ios_base::out | ios_base::binary | ios_base::trunc);

		return file_name;
	}
	const string& operator=(const string& file_name)
	{
		if (writer.is_open())
		{
			writer.close();
		}

		writer.open(file_name, ios_base::out | ios_base::binary | ios_base::trunc);

		return file_name;
	}

public:
	inline void set_flag(WRITERINFO i)
	{
		Message::set_flag((int)i);
		set_info();
	}
	inline WRITERINFO get_flag()
	{
		return (WRITERINFO)Message::get_flag();
	}

public:
	virtual void set_info();

public:
	bool write(const char* p, int size);
};

#endif