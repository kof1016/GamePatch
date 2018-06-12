#include "pch.h"
#include "catch.hpp"
#include "../Utility/IState.h"
#include "../Utility/StateMachine.h"


class FakeState : public Utility::IState
{
public:
	FakeState()
	{
	}

	~FakeState() override
	{
	}

	void Enter() override
	{
		std::cout << "Enter FakeState" << std::endl;
	}

	void Leave() override
	{
		std::cout << "Leave FakeState" << std::endl;
	}

	void Update() override
	{
		std::cout << "Update FakeState" << std::endl;
		OnDone();
	}

	std::function<void()> OnDone;
};

TEST_CASE("state machine test", "[Utility]")
{
	// auto machine = new Utility::StateMachine;
 //
	// const auto fake = new FakeState;
 //
	// fake->OnDone = []()
	// {
	// 	std::cout << "state done" << std::endl;
	// };
 //
	// const std::shared_ptr<Utility::IState> state(fake);
	// machine->Push(state);
	// machine->Update();
 //
	// delete machine;
}
