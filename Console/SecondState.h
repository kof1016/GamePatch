#pragma once
#include <functional>
#include "../Utility/IState.h"

namespace State
{
	class SecondState : public Utility::IState
	{
	public:
		SecondState();
		virtual ~SecondState();
		void Enter() override;
		void Leave() override;
		void Update() override;

		std::function<void()> OnDone;
	};
	
}


