#include "catch.hpp"
#include "../Utility/Receive/ReceiveProgress.h"
#include "../Utility/Receive/ReceiveWriteData.h"
#include "../Utility/Receive/ReceiveDone.h"

using namespace BZbee::Sandbox::GamePatch::Utility;
TEST_CASE("ReceiveProgress before bind", "[Receive]")
{
	//arrange
	int total, downloaded;

	//act
	auto test = Receive::ReceiveProgress();
	test.Bind([&](int t, int d)
	{
		total = t;
		downloaded = d;
	});

	test.Invoke(2, 1);

	//assert
	REQUIRE(total == 2);
	REQUIRE(downloaded == 1);
}

TEST_CASE("ReceiveProgress before invoke", "[Receive]")
{
	//arrange
	int total, downloaded;

	//act
	auto test = Receive::ReceiveProgress();

	test.Invoke(2, 1); //true 

	test.Bind([&](int t, int d)
	{
		total = t;
		downloaded = d;
	});

	//assert
	REQUIRE(total == 2);
	REQUIRE(downloaded == 1);
}

TEST_CASE("ReceiveDone before bind", "[Receive]")
{
	auto test = Receive::ReceiveDone();

	bool done = false;
	test.Bind([&](bool result)
	{
		done = true;
	});

	test.Invoke(true);

	REQUIRE(done == true);
}

TEST_CASE("ReceiveDone before invoke", "[Receive]")
{
	auto test = Receive::ReceiveDone();

	test.Invoke(true); //true 

	bool done = false;
	test.Bind([&](bool result)
	{
		done = true;
	});

	REQUIRE(done == true);
}

TEST_CASE("ReceiveWriteData before bind", "[Receive]")
{
	//arrange
	char source[]{'1', '2', '3', '\0'};
	std::vector<char> target;

	//act
	auto test = Receive::ReceiveWriteData();
	test.Bind
	(
		[&](char* buffer, size_t total)
		{
			target.assign(buffer, buffer + total);
		}
	);

	test.Invoke(source, sizeof(source));

	// assert
	REQUIRE(target.size() == 4);
}

TEST_CASE("ReceiveWriteData before invoke", "[Receive]")
{
	//arrange
	char source[]{'1', '2', '3', '\0'};
	std::vector<char> target;

	//act
	auto test = Receive::ReceiveWriteData();
	test.Invoke(source, sizeof(source)); //true 

	test.Bind
	(
		[&](char* buffer, size_t total)
		{
			target.assign(buffer, buffer + total);
		}
	);

	// assert
	REQUIRE(target.size() == 4);
}
