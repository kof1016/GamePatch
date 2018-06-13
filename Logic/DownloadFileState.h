#pragma once
#include "../Utility/IState.h"
#include <functional>
#include <memory>
#include "../Utility/FileWriter.h"
#include "../Utility/ProgressAdapter.h"

namespace Utility {
	class IDownloadable;
	class ReceiverFacade;
}

namespace Logic
{
	class DownloadFileState final : public Utility::IState
	{
	public:
		typedef std::function<void()> DoneEvent;

		DownloadFileState() = default;
		
		DownloadFileState(std::shared_ptr<Utility::ReceiverFacade> facade, Utility::FileWriter& fileuser);

		~DownloadFileState() override;
		void Enter() override;
		void Leave() override;
		void Update() override;
		
		void OnDoneEvent(DoneEvent&& callback);
		void OnProgressEvent(DataDefine::OnProgress&& callback);

	private:
		std::shared_ptr<Utility::ReceiverFacade> _ReceiverFacade;
		Utility::FileWriter _FileWriter;
		DoneEvent _OnDone;
		DataDefine::OnProgress _OnProgress;
	};
}
