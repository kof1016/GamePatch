#pragma once
#include "IState.h"
#include <queue>
#include <memory>

namespace bZbee::Sandbox::GamePatch::Utility::StateMachine
{
	class StateMachine final
	{
	public:
		StateMachine();
		StateMachine& operator=(const StateMachine&) = delete;
		StateMachine(StateMachine&&) = delete;
		~StateMachine();

		auto CurrentState() const
		{
			return _CurrentState;
		}

		void Push(std::shared_ptr<IState> new_state);

		bool Update();

	private:
		void _SetCurrentState();
		void _UpdateCurrentState() const;

		std::queue<std::shared_ptr<IState>> _StandBys;
		std::shared_ptr<IState> _CurrentState{nullptr};
		
	};
}
