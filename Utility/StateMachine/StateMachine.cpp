#include "StateMachine.h"

namespace BZbee::Sandbox::GamePatch::Utility::StateMachine
{
	StateMachine::StateMachine()
	{
	}

	StateMachine::~StateMachine()
	{
		std::queue<std::shared_ptr<IState>> empty;
		std::swap(empty, _StandBys);

		_CurrentState->Leave();
	}

	void StateMachine::Push(std::shared_ptr<IState> new_state)
	{
		_StandBys.emplace(new_state);
	}

	bool StateMachine::Update()
	{
		_SetCurrentState();
		_UpdateCurrentState();

		return _CurrentState != nullptr;
	}

	void StateMachine::_SetCurrentState()
	{
		if (_StandBys.empty())
		{
			return;
		}

		auto state = _StandBys.front();

		if (state == nullptr)
		{
			return;
		}

		if (_CurrentState != nullptr)
		{
			_CurrentState->Leave();
		}

		state->Enter();
		_CurrentState = state;
		_StandBys.pop();
	}

	void StateMachine::_UpdateCurrentState() const
	{
		if (_CurrentState != nullptr)
		{
			_CurrentState->Update();
		}
	}
}
