#include "pch.h"
#include "catch.hpp"
#include <filesystem>
#include "../Utility/DataDefine.h"
#include "../Utility/FileTool.h"
#include "../Utility/cpplinq.hpp"

#include "../PackingLogic/ScanResourceFolder.h"
#include "../PackingLogic/MergeFileList.h"
#include "../PackingLogic/VersionUpdater.h"



TEST_CASE("merge tets", "[packing]")
{
	Utility::FileList current{};
	std::cout << "current size = " << current.size()<< std::endl;

	Utility::FileList resource
	{
		{"md5-1", "path1"},
		{"md5-2", "path2"},
		{"md5-3", "path3"},
		{"md5-4", "path4"},
		{"md5-5", "path5"},
	};
	std::cout << "resource size = " << resource.size() << std::endl;

	auto mergedList = PackingLogic::MergeFileList(current, resource).Result();
	
	REQUIRE(mergedList.size() == 5);

	std::cout << "merge result" << std::endl;
	for (auto& r : mergedList)
	{
		REQUIRE(r.StateSymbol == "+");
		std::cout << r.StateSymbol << "|" << r.MD5 << "|" << r.Path << std::endl;
	}
}


TEST_CASE("ScanResourceFolder test", "[packing]")
{
	const auto path = Utility::RESOURCE_FOLDER_NAME;

	PackingLogic::ScanResourceFolder maker(path);

	const auto reuslt = maker.Make();

	for (auto& r : reuslt)
	{
		std::cout << "MD5= " << r.MD5 << "Path= " << r.Path << std::endl;
	}

	REQUIRE(reuslt.size() ==5);
}

TEST_CASE("update ver test", "[packing]")
{

	//test
	auto currentVer = 0;
	PackingLogic::VersionUpdater updater(currentVer);
	auto newestVer = updater.UpdateVer();

	std::cout << "currentVer= " << currentVer << std::endl;
	std::cout << "newestVer= " << newestVer << std::endl;

	REQUIRE(newestVer == currentVer +1);
}

TEST_CASE("save filelist test", "[packing]")
{
	//arrange
	int newestVer = 1;
	Utility::FileList files
	{
		{"+", "1", "path1"},
		{"+", "2", "path2"},
		{"+", "3", "path3"},
		{"+", "4", "path4"},
		{"+", "5", "path5"},
	};

	auto saveTarget = Utility::FileListSavePath(newestVer);

	auto aa = absolute(saveTarget);


	if (!exists(saveTarget.parent_path()))
	{
		create_directories(saveTarget.parent_path());
	}

	std::ofstream outfile(saveTarget, std::ofstream::out); //write mode

	for (auto& c : files)
	{
		outfile << c.StateSymbol << "|" << c.MD5 << "|" << c.Path << std::endl;
	}

	outfile.close();
}

TEST_CASE("Create zip test", "[packing]")
{
	//arrange
	Utility::FileList _FileList
	{
		{"-", "1", "resource/art/1.txt"},
		{"+", "2", "resource/art/2.txt"},
		// {"-", "3", "3.txt"},
		// {"-", "4", "path4"},
		// {"-", "5", "path5"},
	};

	namespace fs = std::experimental::filesystem;

	path target(Utility::FileListSavePath(1));

	for (auto& d : _FileList)
	{
		if (d.StateSymbol == "+")
		{
			auto sourceFile = path(d.Path);
			const auto targetFolder = target.parent_path() / sourceFile.parent_path();

			if (!exists(targetFolder))
			{
				create_directories(targetFolder);
			}
			copy_file(sourceFile, targetFolder / sourceFile.filename(), copy_options::overwrite_existing);
		}
	}
}

TEST_CASE("copy file", "[packing]")
{
	//arrangeMergeFileList
	namespace fs = std::experimental::filesystem;

	path sourceFile = "Resource/art/1.txt";
	path targetParent = "ResourcePack/";

	auto sourceParent = sourceFile.parent_path();

	auto targetFolder = targetParent / sourceParent; // sourceFile.filename() returns "sourceFile.ext".

	if (!exists(targetFolder))
	{
		create_directories(targetFolder);
	}
	copy_file(sourceFile, targetFolder / sourceFile.filename(), copy_options::overwrite_existing);

	
}
