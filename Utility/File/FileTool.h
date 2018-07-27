#pragma once
#include <string>
#include <fstream>
#include "md5.h"
#include <filesystem>
#include <assert.h>
#include <minizip/zip.h>
#include <minizip/unzip.h>
#include "../PackingLogic/SaveDataAdapter.h"

using namespace std::experimental::filesystem ;

namespace FileTool
{
	static _off_t GetFileSize_C(std::string& path)
	{
		struct stat fileStat{};

		const _off_t ret = stat(path.c_str(), &fileStat);

		if (ret == 0)
		{
			return fileStat.st_size;
		}
		return ret;
	}

	static std::ifstream::pos_type GetFileSize_CPlusPlus(std::string& filename)
	{
		std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
		return in.tellg();
	}

	static bool ReadFileToBuffer(const std::string& file_path, std::vector<char>& buffer)
	{
		std::ifstream infile(file_path, std::ios::in | std::ios::ate); //read mode | read to end


		if (!infile.is_open())
		{
			std::string msg = "open file error = " + file_path;
			//assert(false && msg.c_str());
			//return false;
			buffer.resize(0);
			return false;
		}


		const auto size = infile.tellg();

		buffer.resize(size);

		infile.seekg(0, std::ios::beg);
		infile.read(buffer.data(), size);
		infile.close();

		return true;
	}

	static bool ReadFileToBufferToBinary(const std::string& file_path, std::vector<char>& buffer)
	{
		std::ifstream infile(file_path, std::ios::binary | std::ios::in | std::ios::ate); //read mode | read to end


		if (!infile.is_open())
		{
			std::string msg = "open file error = " + file_path;
			//assert(false && msg.c_str());
			//return false;
			buffer.resize(0);
			return false;
		}


		const auto size = infile.tellg();

		buffer.resize(size);

		infile.seekg(0, std::ios::beg);
		infile.read(buffer.data(), size);
		infile.close();

		return true;
	}

	static std::string CreateMD5(std::vector<char>& buffer)
	{
		MD5 md5;
		md5.update(reinterpret_cast<unsigned char*>(buffer.data()), buffer.size());
		md5.finalize();
		return md5.hexdigest();
	}

	static void CreateDir(const path& path)
	{
		if (!exists(path))
		{
			create_directories(path);
		}
	}

	static void CreateZipFromSaveList(Utility::SaveList save_list, const std::string& target_path)
	{
		const auto zFile = zipOpen(target_path.data(), APPEND_STATUS_CREATE);

		for (auto& p : save_list)
		{
			zip_fileinfo zFileInfo;

			auto ret = zipOpenNewFileInZip(
				zFile, 
				p.SaveName.data(), 
				&zFileInfo, 
				nullptr, 0, 
				nullptr, 0, 
				nullptr, 0,
				Z_DEFAULT_COMPRESSION);
			
			if (ret != ZIP_OK)
			{
				std::cout << "openfile in zip failed" << std::endl;
				zipClose(zFile, nullptr);
				return;
			}
			std::vector<char> buffer;
			ReadFileToBufferToBinary(p.Path, buffer);
			ret = zipWriteInFileInZip(zFile, buffer.data(), buffer.size());

			if (ret != ZIP_OK)
			{
				std::cout << "write in zip failed" << std::endl;
				zipClose(zFile, nullptr);
				return;
			}
		}

		zipClose(zFile, nullptr);
		std::cout << "zip ok" << std::endl;
	}

	static void UnZipToDisk(const std::string& zip_file_name)
	{
		const auto READ_SIZE = 8192;
		const auto FILENAME_SIZE = 512;

		// Open the zip file  
		const auto zipfile = unzOpen(zip_file_name.data());
		if (zipfile == nullptr)
		{
			std::cout << "not found\n";
			return;
		}

		// Get info about the zip file  
		unz_global_info global_info;
		if (unzGetGlobalInfo(zipfile, &global_info) != UNZ_OK)
		{
			std::cout << "could not read file global info\n";
			unzClose(zipfile);
			return;
		}

		// Buffer to hold data read from the zip file.  
		char read_buffer[READ_SIZE]{'0'};

		for (auto i = 0; i < global_info.number_entry; ++i)
		{
			// Get info about current file.  
			unz_file_info file_info;
			char filename[FILENAME_SIZE]{'0'};

			if (unzGetCurrentFileInfo(
				zipfile,
				&file_info,
				filename,
				FILENAME_SIZE,
				nullptr, 0, nullptr, 0) != UNZ_OK)
			{
				std::cout << "could not read file info\n";
				unzClose(zipfile);
				return;
			}

			// Check if this entry is a directory or file.  
			if (!path(filename).has_extension())
			{
				CreateDir(path(filename));
			}
			else
			{
				if (unzOpenCurrentFile(zipfile) != UNZ_OK)
				{
					std::cout << "could not open file\n";
					unzClose(zipfile);
					return;
				}

				// Open a file to write out the data.  
				CreateDir(path(filename).parent_path());

				FILE* out;
				if (fopen_s(&out, filename, "wb") != 0)
				{
					std::cout << "could not open destination file" << std::endl;
					unzCloseCurrentFile(zipfile);
					unzClose(zipfile);
					return;
				}

				int error = UNZ_OK;
				do
				{
					error = unzReadCurrentFile(zipfile, read_buffer, READ_SIZE);
					if (error < 0)
					{
						std::cout << "error=" << error << std::endl;
						unzCloseCurrentFile(zipfile);
						unzClose(zipfile);
						return;
					}

					// Write data to file.  
					if (error > 0)
					{
						fwrite(read_buffer, error, 1, out); // You should check return of fwrite...  
					}
				}
				while (error > 0);

				fclose(out);
			}

			unzCloseCurrentFile(zipfile);

			// Go the the next entry listed in the zip file.  
			if (i + 1 < global_info.number_entry)
			{
				if (unzGoToNextFile(zipfile) != UNZ_OK)
				{
					std::cout << "cound not read next file\n";
					unzClose(zipfile);
					return;
				}
			}
		}

		unzClose(zipfile);
	}
}
