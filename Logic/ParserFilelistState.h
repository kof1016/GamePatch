#pragma once
#include "../Utility/IState.h"
#include "../Utility/DataDefine.h"

namespace Logic
{
	typedef std::function<void(DataDefine::ShareFileList, DataDefine::ShareFileList)> OnCheckVersion;
	
	class ParserFilelistState final : public Utility::IState
	{
	public:
		ParserFilelistState();
		~ParserFilelistState();
		void Enter() override;
		void Leave() override;
		void Update() override;
		void DoneEvent(OnCheckVersion&& callback);
	private:
		
		OnCheckVersion _OnDone;
	};
}
