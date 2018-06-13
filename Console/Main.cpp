// Main.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <conio.h>
#include "../Utility/StateMachine.h"
#include "../Logic/FirstState.h"
#include "../Logic/SecondState.h"
#include "../Logic/UpdateLauncher.h"

// Utility::StateMachine StateMachine;
//
//   void _ToSecondState()
//   {
//   	const auto state = new State::SecondState();
//   	//state->OnDone = &_ToSecondState;
// 	const std::shared_ptr<Utility::IState> s(state);
//   	StateMachine.Push(s);
//   }
//
//   void _ToFirstState()
//   {
//   	const auto state = new State::FirstState();
//   	state->OnDone = &_ToSecondState;
// 	const std::shared_ptr<Utility::IState> s(state);
//   	StateMachine.Push(s);
//   }

int main(int argc, char* argv[])
{
	Logic::UpdateLauncher launcher;

	launcher.Start();

	launcher.OnDownloadProgress
	(
		[=](int total_size, int downloaded_size)
		{
			const auto percent = downloaded_size * 100.0 / total_size;
			std::cout << "percent=" << percent << "\r";
			// game ui
		}
	);

	int n = _kbhit();
	std::cout << "input 1 to exit" << std::endl;

	while (true)
	{
		if (_kbhit() != 0)
		{
			if (_getch() == 0x31)
			{
				std::cout << "exit" << std::endl;
				break;
			}
		}
		launcher.Update();
	}

	return 0;
}
