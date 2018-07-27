#pragma once
#include "../../Utility/StateMachine/IState.h"
#include <functional>
#include <memory>
#include "../../Utility/File/FileWriter.h"
#include "../../Utility/Curl/ProgressAdapter.h"
#include "../../Utility/Receive/ReceiverFacade.h"

// namespace Utility {
// 	class IDownloadable;
// 	class ReceiverFacade;
// }

namespace BZbee::Sandbox::GamePatch::UpdateLogic::State
{
	class DownloadFileState final : public Utility::StateMachine::IState
	{
	public:
		typedef std::function<void()> DoneEvent;

		DownloadFileState() = default;
		
		DownloadFileState(std::shared_ptr<Utility::Receive::ReceiverFacade> facade, Utility::File::FileWriter& file_writer);

		~DownloadFileState() override;
		void Enter() override;
		void Leave() override;
		void Update() override;
		
		void OnDoneEvent(DoneEvent&& callback);
		void OnProgressEvent(Utility::DataDefine::OnProgress&& callback);

	private:
		std::shared_ptr<Utility::Receive::ReceiverFacade> _ReceiverFacade;
		Utility::File::FileWriter _FileWriter;
		DoneEvent _OnDone;
		Utility::DataDefine::OnProgress _OnProgress;
	};
}
