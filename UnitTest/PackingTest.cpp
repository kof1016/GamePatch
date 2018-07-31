#include "catch.hpp"
#include <filesystem>
#include "../Utility/DataDefine.h"
#include "../Utility/File/FileTool.h"
#include "../PackingLogic/Step/ScanResourceFolder.h"
#include "../PackingLogic/Step/MergeFileList.h"
#include "../PackingLogic/Step/VersionUpdater.h"


using namespace bZbee::Sandbox::GamePatch::PackingLogic;
using namespace bZbee::Sandbox::GamePatch::Utility;
TEST_CASE("merge tets", "[packing]")
{
	DataDefine::FileList current{};
	std::cout << "current size = " << current.size()<< std::endl;

	DataDefine::FileList resource
	{
		{"md5-1", "path1"},
		{"md5-2", "path2"},
		{"md5-3", "path3"},
		{"md5-4", "path4"},
		{"md5-5", "path5"},
	};
	std::cout << "resource size = " << resource.size() << std::endl;

	auto mergedList = Step::MergeFileList(current, resource).Result();
	
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
	const auto path = DataDefine::RESOURCE_FOLDER_NAME;

	Step::ScanResourceFolder maker(path);

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
	Step::VersionUpdater updater(currentVer);
	auto newestVer = updater.UpdateVer();

	std::cout << "currentVer= " << currentVer << std::endl;
	std::cout << "newestVer= " << newestVer << std::endl;

	REQUIRE(newestVer == currentVer +1);
}

TEST_CASE("save filelist test", "[packing]")
{
	//arrange
	int newestVer = 1;
	DataDefine::FileList files
	{
		{"+", "1", "path1"},
		{"+", "2", "path2"},
		{"+", "3", "path3"},
		{"+", "4", "path4"},
		{"+", "5", "path5"},
	};

	auto saveTarget = DataDefine::FileListSavePath(newestVer);

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