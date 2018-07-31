#include "catch.hpp"
#include "../Utility/StateMachine/IState.h"
#include "../Utility/StateMachine/StateMachine.h"
#include <iostream>

using namespace bZbee::Sandbox::GamePatch::Utility;

class FakeState final : public StateMachine::IState
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
		std::cout << "UpdateToFile FakeState" << std::endl;
		OnDone();
	}

	std::function<void()> OnDone;
};

TEST_CASE("state machine test", "[Utility]")
{
	 auto machine = new StateMachine::StateMachine;
 
	 const auto fake = new FakeState;

	 bool bDone = false;
	 fake->OnDone = [&]()
	 {
	 	std::cout << "state done" << std::endl;
		bDone = true;
	 };
 
	 const std::shared_ptr<StateMachine::IState> state(fake);
	 machine->Push(state);
	 machine->Update();
 
	 delete machine;
	 
	REQUIRE(bDone== true);
}
