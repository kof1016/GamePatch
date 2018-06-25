#include "PackingLauncher.h"
#include "GetCurrentVerStep.h"
#include "CreateNewestVerDoc.h"
#include "GetFileList.h"
#include "CompareResourcePath.h"
#include <filesystem>
#include <string>

#include "FileListMaker.h"



namespace FileListMaker
{
	PackingLauncher::PackingLauncher()
	{
	}

	PackingLauncher::~PackingLauncher()
	{
	}

	void PackingLauncher::Start()
	{
		//step1
		GetCurrentVerStep step1;
		const auto ver = step1.Result();

		//step2
		namespace fs = std::experimental::filesystem;
		auto current = fs::current_path();
		auto filelistPath = current / "ResourcePack" / ("ver" + std::to_string(ver))/ ("filelist_" + ("ver" + std::to_string(ver) + ".txt"));
		
		GetFileList step2(filelistPath.string());
		auto packfilelist = step2.Result();

		//step3
		namespace fs = std::experimental::filesystem;
		current = fs::current_path();
		auto input = current / "Resource";

		FileListMaker maker(input.string(), filelistPath.string());
		auto newfileList = maker.Make();
		
		//CompareResourcePath step3;


		//CreateNewestVerDoc step3(ver);



		// void FileListMaker::_ComparisonLastVer()
		// {
		// }
  //
		// void FileListMaker::_CreateFileList()
		// {
		// 	const auto fileName = std::to_string(_Version) + "filelist.txt";
		// 	const std::experimental::filesystem::path p1(_OutputPath);
		// 	auto p2 = p1 / fileName;
  //
		// 	std::ofstream outfile(p2.string(), std::ofstream::out); //write mode
  //
		// 	outfile << "buildversion=" << _CurrentFileList.Version << std::endl;
  //
		// 	for (auto& c : _CurrentFileList.Contents)
		// 	{
		// 		outfile << c.first << "|" << c.second.Path << std::endl;
		// 	}
  //
		// 	outfile.close();
		// }
	}

	void PackingLauncher::Update()
	{
	}

	void PackingLauncher::Shutdown()
	{
	}
}
