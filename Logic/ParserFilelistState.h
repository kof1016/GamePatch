#pragma once
#include "../Utility/IState.h"
#include "../Utility/DataDefine.h"

namespace Logic
{
	class ParserFilelistState final : public Utility::IState
	{
	public:
		
		typedef std::function<void(DataDefine::FileList, DataDefine::FileList)> DoneEvent;
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
