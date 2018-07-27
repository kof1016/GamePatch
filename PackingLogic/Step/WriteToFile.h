#pragma once
#include <string>
#include <list>
#include "../Utility/FileWriter.h"
#include "../Utility/DataDefine.h"
#include <iostream>
#include <fstream>

namespace PackingLogic
{
	template <typename T1>
	class WriteToFile
	{
	public:
		WriteToFile() = delete;
		~WriteToFile() = delete;
	};

	template <>
	class WriteToFile<std::string>
	{
	public:
		WriteToFile() = delete;

		WriteToFile(std::string path, std::string content)
			: _Path(std::move(path))
			, _Content(std::move(content))

		{
		}

		void Write()
		{
			std::ofstream outfile(_Path, std::ofstream::out); //write mode
			outfile << _Content.data();
			outfile.close();
		}

	private:
		std::string _Path;
		std::string _Content;
	};
	typedef class WriteToFile<std::string> WriteFileFromString;
	typedef WriteFileFromString CreateNewestVerFile;

	template <>
	class WriteToFile<Utility::FileList>
	{
	public:
		WriteToFile() = delete;

		WriteToFile(std::string path, Utility::FileList content)
			: _Path(path)
			, _FileList(std::move(content))

		{
		}

		void Write()
		{
			std::ofstream outfile(_Path, std::ofstream::out); //write mode

			for (auto& c : _FileList)
			{
				outfile << c.StateSymbol << "|" << c.MD5 << "|" << c.Path << std::endl;
			}

			outfile.close();
		}

	private:
		std::string _Path;
		Utility::FileList _FileList;
	};
	typedef class WriteToFile<Utility::FileList> WriteFileFromList;
	typedef WriteFileFromList CreateFileListFile;
}