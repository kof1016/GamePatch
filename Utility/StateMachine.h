#pragma once
#include "IState.h"
#include <queue>

namespace Utility
{
	class StateMachine final
	{
	public:
		StateMachine();
		StateMachine& operator=(const StateMachine&) = delete;
		StateMachine(StateMachine&& ) = delete;
		~StateMachine();

		IState* CurrentState() const;

		void Push(IState* new_state);

		bool Update();

		void Termination();

		void Empty();

	private:
		void _SetCurrentState();
		void _UpdateCurrentState() const;
		void _Clear(std::queue<IState*>& q) const;

	private:
		std::queue<IState*> _StandBys;
		IState* _CurrentState{nullptr};
	};
}

