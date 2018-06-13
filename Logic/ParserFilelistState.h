#pragma once
#include "../Utility/IState.h"
#include "../Utility/DataDefine.h"

namespace Logic
{
	class ParserFilelistState final : public Utility::IState
	{
	public:
		
		typedef std::function<void(DataDefine::ShareFileList, DataDefine::ShareFileList)> DoneEvent;
		typedef std::function<void()> FinalEvent;
		
		ParserFilelistState();
		~ParserFilelistState();
		void Enter() override;
		void Leave() override;
		void Update() override;
		void OnDoneEvent(DoneEvent&& callback);
	private:

		DoneEvent _OnDoneEvent;
	};
}
