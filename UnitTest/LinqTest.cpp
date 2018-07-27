#include "catch.hpp"
#include "../Utility/Linq/cpplinq.hpp"
#include "../Utility/File/DataParser.h"
#include <iostream>


TEST_CASE("linq test", "[linq]")
 {
 	BZbee::Sandbox::GamePatch::Utility::DataDefine::FileList currentdata =
 	{
 		{"1", "path1"},
 		{"2", "path2"},
 		{"3", "path3"},
 	};

 	BZbee::Sandbox::GamePatch::Utility::DataDefine::FileList sourcedata =
 	{
 		{"1", "path1"},
 		{"2", "path2"},
 		{"5", "path5"},
 	};

 	using namespace cpplinq;

 	const auto c = from(currentdata)
 		>> select([](auto d) { return d.MD5; })
 		>> to_list();

 	const auto s = from(sourcedata)
 		>> select([](auto d) { return d.MD5; })
 		>> to_list();

 	auto remove = from(c)
 		>> except(from(s))
 		>> to_list();

 	auto add = from(s)
 		>> except(from(c))
 		>> to_list();

 	auto result = from(add)
 		>> select([&](auto key)
 		{
 			const auto r = std::find_if(sourcedata.begin(), sourcedata.end(),
 										[&](auto& d)
 										{
 											if (key == d.MD5)
 											{
 												d.StateSymbol = "+";
 											}

 											return key == d.MD5;
 										});
 			return *r;
 		})
 		>> to_list();

 	auto result2 = from(remove)
 		>> select([&](auto key)
 		{
 			const auto r = std::find_if(currentdata.begin(), currentdata.end(),
 										[&](auto& d)
 										{
 											if (key == d.MD5)
 											{
 												d.StateSymbol = "-";
 											}

 											return key == d.MD5;
 										});
 			return *r;
 		})
 		>> to_list();

 	result.insert(result.end(), result2.begin(), result2.end());

 	std::cout << "result size= " << result.size() << std::endl;
 	REQUIRE(result.size() == 2);
 	
 	for (auto r : result)
 	{
 		std::cout << "state= " << r.StateSymbol << "   MD5= " << r.MD5 << "   path= " << r.Path << std::endl;
 	}
 	
 }
