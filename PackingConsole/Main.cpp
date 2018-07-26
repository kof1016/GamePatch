// PackingTool.cpp : Defines the entry point for the console application.
//


#include "../PackingLogic//PackingLauncher.h"
#include <conio.h>
#include <iostream>

int main()
{
	std::cout << "====================================" << std::endl;
	std::cout << "resource packing tool" << std::endl;
	std::cout << "this tool can create resoucre zip file to [ResourcePack] folder." << std::endl;
	std::cout << "support check diff last version resource" << std::endl;
	std::cout << "create file list to merge" << std::endl;
	std::cout << "auto add version number, current version number rule is add 1" << std::endl;
	std::cout << "====================================" << std::endl;
	std::cout << "press any key to start packing resource" << std::endl;

	_getch();

	PackingLogic::PackingLauncher launcer;

	launcer.Start();
    
	return 0;
}

