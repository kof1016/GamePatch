#include "FirstState.h"
#include <iostream>
#include <conio.h>


namespace State
{
	FirstState::FirstState()
	{
		
	}

	FirstState::~FirstState()
	{
	}

	void FirstState::Enter()
	{
		std::cout << "Enter FirstState" << std::endl;

		std::cout << "input 1 to second state" << std::endl;
	}

	void FirstState::Leave()
	{
		std::cout << "Leave FirstState" << std::endl;
	}

	void FirstState::Update()
	{
		if(_kbhit() != 0)
		{
			if (_getch() == 0x31)
			{
				OnDone();
			}
			
		}
	}
}
