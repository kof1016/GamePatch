#include "StateMachine.h"


namespace Utility
{
	StateMachine::StateMachine()
	{
	}

	StateMachine::~StateMachine()
	{
	}

	IState* StateMachine::CurrentState() const
	{
		return _CurrentState;
	}

	void StateMachine::Push(IState* new_state)
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

	void StateMachine::Termination()
	{
		_Clear(_StandBys);

		if (_CurrentState == nullptr)
		{
			return;
		}

		_CurrentState->Leave();
		_CurrentState = nullptr;
	}

	void StateMachine::_Clear(std::queue<IState*>& q) const
	{
		std::queue<IState*> empty;
		std::swap(empty, q);
	}

	void StateMachine::Empty()
	{
		//Push(new EmptyStage());
	}
}
