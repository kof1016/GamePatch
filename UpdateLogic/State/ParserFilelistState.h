#pragma once
#include "../../Utility/StateMachine/IState.h"
#include "../../Utility/DataDefine.h"

namespace UpdateLogic
{
	class ParserFilelistState final : public Utility::IState
	{
	public:
		
		typedef std::function<void(Utility::FileData, Utility::FileData)> DoneEvent;
		typedef std::function<void()> FailEvent;
		
		
		ParserFilelistState();
		~ParserFilelistState();
		void Enter() override;
		void Leave() override;
		void Update() override;
		void OnDoneEvent(DoneEvent&& callback);
		void OnFailEvent(FailEvent&& callback);
	
	private:
		DoneEvent _OnDoneEvent;
		FailEvent _OnFailEvent;
	};
}
