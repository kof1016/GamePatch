#include "pch.h"
#include "catch.hpp"
#include "../Utility/md5.h"
#include <fstream>
#include <experimental/filesystem>
#include <unordered_map>
#include "../Utility/ConfigParser.h"

// TEST_CASE("ComparisonLastVer test", "[file]")
// {
// 	//arrange
// 	const int ver = 1;
// 	std::string inputpath = "resource";
// 	std::string outputpath = "resource_pack/ver" + std::to_string(ver);
// 	
// 	//act
// 	namespace fs = std::experimental::filesystem;
// 	fs::current_path();
//
// 	 
//
// 	 Utility::FileListMaker maker(inputpath, outputpath, ver);
// }

  

  

  class Step3
  {
  public:
	  Step3(int i)
	  {
		  money = i;
	  }
	  int Return()
	  {
		  return 3;
	  }
	  int money;
  };
  class Step2
  {
  public:
	  Step2(int i)
	  {
		  money = i;
	  }

	  int Return()
	  {
		  return 2;
	  }
	  int money;
  };
  class Step1
  {
  public:
	  Step1() {};
	  int Return()
	  {
		  return 1;
	  }
  };

 TEST_CASE("Pipeline test", "[file]")
 {
	auto step1 = Step1();
	auto step2 = Step2(step1.Return());
	auto step3 = Step3(step2.Return());
	REQUIRE(step3.Return() == 3);
 }

TEST_CASE("Filesystem test", "[file]")
{
	std::string ver = "1";
	namespace fs = std::experimental::filesystem;
	fs::create_directories("resource_pack/ver" + ver);

	fs::create_directories("sandbox/1/2/a");
	fs::create_directory("sandbox/1/2/b");

	fs::create_directory("sandbox/1/2/c", "sandbox/1/2/b");

	std::experimental::filesystem::path p1("c:\\windows");
	std::experimental::filesystem::path p2 = p1 / "system32";
}


TEST_CASE("FileListMaker test", "[file]")
{
	
	const std::string path{ R"(..\resources\)" };
	const int version = 1;

	//Utility::FileListMaker maker(path, version);
}

TEST_CASE("unordered_map test", "[file]")
{
	std::unordered_map<std::string, std::string> map{{"1", "1"}, {"1", "2"}, {"1", "3"}};

	const auto r = map.find("1");

	if (r != map.end())
	{
		std::cout << "Found " << r->first << " " << r->second << '\n';
	}
	else
	{
		std::cout << "Not found\n";
	}
}

TEST_CASE("find data diff", "[file]")
{
	//arrange
	std::unordered_map<int, int>local{ {1,1} };
	std::unordered_map<int, int>remote{ { 1,1 }, { 2,1 },{ 3,1 } };
	std::unordered_map<int, int>diff;

	//act
	for(auto& e : remote)
	{
		const auto r = local.find(e.first);
		if(r == local.end())
		{
			diff.insert(e);
		}
	}

	//assert
	REQUIRE(diff.size() == 2);
	REQUIRE(diff.at(2) == 1);
	REQUIRE(diff.at(3) == 1);
}



TEST_CASE("config parser", "[file]")
{
	//arrange
	const std::string data =
		"buildversion=1"
		"actions/1.png|9e107d9d372bb6826bd81d3542a419d6";
	//act
	Utility::ConfigParser parser;

	auto filelist = parser.Load(data);

	// assert
	REQUIRE(filelist.Version == 1);

	const auto r = filelist.Contents.find("actions/1.png");

	REQUIRE(r != filelist.Contents.end());

	REQUIRE(r->first == "9e107d9d372bb6826bd81d3542a419d6");
}

TEST_CASE("MD5_C_Style", "[file]")
{
	std::FILE* fp = std::fopen("dummy.txt", "w");
	assert(fp);

	std::fseek(fp, 0, SEEK_END); // seek to end
	const std::size_t filesize = std::ftell(fp);

	std::fseek(fp, 0, SEEK_SET); // seek to start
	std::vector<uint8_t> buffer(filesize);

	std::fread(buffer.data(), sizeof(uint8_t), buffer.size(), fp);

	MD5 md5;
	md5.update(buffer.data(), buffer.size());
	md5.finalize();

	const auto strMd5 = md5.hexdigest();

	std::fclose(fp);
	std::printf("i've read %zi bytes\n", filesize);

	std::string a = "327c478cce88005e6ad0d5ad10811b11";

	a.compare(strMd5);

	std::cout << strMd5 << std::endl;
}


TEST_CASE("MD5-2", "[file]")
{
	std::ifstream infile(R"(..\resources\1.txt)", std::ios::in | std::ios::ate); //read mode | read to end

	if (!infile.is_open())
	{
		int i = 0;
		assert("open file error, testfile.txt");
		return;
	}

	const auto size = infile.tellg();

	std::vector<unsigned char> buffer(size);

	infile.seekg(0);
	infile.read(reinterpret_cast<char*>(buffer.data()), size);
	infile.close();

	MD5 md5;
	md5.update(buffer.data(), buffer.size());
	md5.finalize();
	const auto strmd5 = md5.hexdigest();

	auto oldmd5 = "9d5826b31abc288c9587276fc74d98a1";

	auto oldmd = "buildversion=1\r\nactions/1.png|123\r\n";

	std::ofstream outfile("md5list.txt", std::ofstream::out | std::ofstream::app); //write mode | write data from eof 

	outfile << buffer.data() << std::endl;
	outfile << "dm5 = " << strmd5.data() << std::endl << std::endl;

	outfile.close();
}
