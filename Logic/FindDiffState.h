#pragma once
#include "../Utility/IState.h"
#include "../Utility/DataDefine.h"

namespace Logic
{
	class FindDiffState final : public Utility::IState
	{
	public:
		FindDiffState(DataDefine::ShareFileList local, DataDefine::ShareFileList remote);
		~FindDiffState();
		void Enter() override;
		void Leave() override;
		void Update() override;
	private:
		DataDefine::ShareFileList _Local;
		DataDefine::ShareFileList _Remote;
		
		DataDefine::FileListData _List;

	};
}
