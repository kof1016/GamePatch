
#include "SecondState.h"
#include <iostream>

namespace State
{
	SecondState::SecondState()
	{
	}

	SecondState::~SecondState()
	{
	}

	void SecondState::Enter()
	{
		std::cout << "Enter SecondState" << std::endl;
	}

	void SecondState::Leave()
	{
		std::cout << "Leave SecondState" << std::endl;
		OnDone = []()
		{
			std::cout << "Leave SecondState" << std::endl;
		};
	}

	void SecondState::Update()
	{
		//std::cout << "Update SecondState" << std::endl;
	}
}
