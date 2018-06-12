#pragma once
#include "../Utility/IState.h"
#include <functional>
#include <memory>
#include "../Utility/FileWriter.h"

namespace Utility {
	class IDownloadable;
	class ReceiverFacade;
}

namespace Logic
{
	class GetRemoteFileState final : public Utility::IState
	{
	public:
		GetRemoteFileState() = default;
		
		GetRemoteFileState(std::shared_ptr<Utility::ReceiverFacade> facade, const Utility::FileWriter& fileuser);

		~GetRemoteFileState() override;
		void Enter() override;
		void Leave() override;
		void Update() override;
		
		void DoneEvent(std::function<void()>&& callback);

	private:
		std::shared_ptr<Utility::ReceiverFacade> _ReceiverFacade;
		const Utility::FileWriter& _FileUser;
		std::function<void()> _OnDone;
	};
}
