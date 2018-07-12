// Main.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <conio.h>
#include "../Logic/UpdateLauncher.h"


int main(int argc, char* argv[])
{
	UpdateLogic::UpdateLauncher launcher;

	launcher.OnDownloadProgress([=](int total_size, int downloaded_size)
	{
		const auto percent = downloaded_size * 100.0 / total_size;
		std::cout << "percent=" << percent << "\r";
		// game using interface
	});

	bool done = false;
	launcher.OnUpdateSuccessEvent([&]()
	{
		std::cout << "all download success" << std::endl;
		std::cout << "ready to game" << std::endl;
		done = true;
		// game using interface
	});

	launcher.OnNotNeedEvent([&]()
	{
		std::cout << "remote ver = local ver" << std::endl;
		std::cout << "need not update" << std::endl;
		std::cout << "ready to game" << std::endl;
		done = true;
		// game using interface
	});

	std::cout << "====================================" << std::endl;
	std::cout << "remote update tool " << std::endl;
	std::cout << "press any key to start update" << std::endl;

	_getch();

	launcher.Start();
	std::cout << "update starting" << std::endl;

	while (!done)
	{
	}

	return 0;
}
