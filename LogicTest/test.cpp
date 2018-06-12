#include "pch.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../Logic/GetRemoteFileState.h"
#include "../Utility/HttpDownload.h"
#include "../Utility/FileWriter.h"


TEST_CASE("GetRemoteFileState", "[logic]")
{
	// Utility::HttpDownload download ; //user
	// const auto facade = download.Start("123");
	// const Utility::FileWriter fileuser("testfile");
 //
	// auto state = new Logic::GetRemoteFileState(facade, fileuser);
 //
	// state->DoneEvent([]() {});
}