#pragma once
#include "../../Utility/StateMachine/IState.h"
#include <functional>
#include <memory>
#include "../../Utility/File/FileWriter.h"
#include "../../Utility/Curl/ProgressAdapter.h"

namespace Utility {
	class IDownloadable;
	class ReceiverFacade;
}

namespace UpdateLogic
{
	class DownloadFileState final : public Utility::IState
	{
	public:
		typedef std::function<void()> DoneEvent;

		DownloadFileState() = default;
		
		DownloadFileState(std::shared_ptr<Utility::ReceiverFacade> facade, Utility::FileWriter& file_writer);

		~DownloadFileState() override;
		void Enter() override;
		void Leave() override;
		void Update() override;
		
		void OnDoneEvent(DoneEvent&& callback);
		void OnProgressEvent(Utility::OnProgress&& callback);

	private:
		std::shared_ptr<Utility::ReceiverFacade> _ReceiverFacade;
		Utility::FileWriter _FileWriter;
		DoneEvent _OnDone;
		Utility::OnProgress _OnProgress;
	};
}
