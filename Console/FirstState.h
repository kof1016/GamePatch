#pragma once
#include <functional>
#include "../Utility/IState.h"


namespace State
{
	class FirstState : public Utility::IState
	{
	public:
		FirstState();
		virtual ~FirstState();
		void Enter() override;
		void Leave() override;
		void Update() override;

		std::function<void()> OnDone;

	};
}


