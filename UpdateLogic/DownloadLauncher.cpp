#include "DownloadLauncher.h"
#include "State/DownloadFileState.h"
#include "State/ParserFilelistState.h"
#include "State/FindDiffState.h"
#include <filesystem>
#include <iostream>
#include "../Utility/File/FileTool.h"
#include "../Utility/File/DataParser.h"

namespace bZbee::Sandbox::GamePatch::DownloadLogic::Launcher
{
	DownloadLauncher::DownloadLauncher()
	{
	}


	DownloadLauncher::~DownloadLauncher()
	{
	}

	void DownloadLauncher::Start()
	{
		Utility::File::CreateDir(Utility::DataDefine::PACKING_FOLDER_NAME);

		_ToDownloadNewestVer();
	}

	void DownloadLauncher::_ToDownloadNewestVer()
	{
		path filePath = Utility::DataDefine::NewestVerSavePath();;
		const auto url = Utility::DataDefine::FilePathToUrl(filePath);
		const auto facade = _DownloadProvider.Start(url);
		Utility::File::FileWriter fileWriter(filePath.string(),"w");

		auto dfs = new State::DownloadFileState(facade, fileWriter);
		
		dfs->Enter();

		dfs->OnProgressEvent([=](int total_size, int downloaded_size)
		{
			_OnProgress(total_size, downloaded_size);
		});

		dfs->OnDoneEvent([=]()
		{
			_ToParserVerNumberState(filePath);
		});
	}

	void DownloadLauncher::_ToParserVerNumberState(path file_path)
	{
		const auto newestVer = Utility::File::DataParser::ParserVersionNumberByFile(file_path.string());

		const auto localVer = Utility::File::DataParser::ParserVersionNumberByFile(Utility::DataDefine::LocalVerSavePath().string());

		if(localVer == newestVer)
		{
			_RemoveDownloadPack();
			_OnNotNeed();
		}
		else
		{
			_ToDiffVerNumberState(localVer, newestVer);
		}
	}

	void DownloadLauncher::_ToDiffVerNumberState(int local_ver, int newest_ver)
	{
		for (int i = local_ver + 1; i <= newest_ver; ++i)
		{
			auto path = Utility::DataDefine::ZipFileSavePath(i);
			_DownloadList.emplace(path);
			_FilePaths.emplace(i, path);
		}
		
		_ToDownloadFileState();
	}

	void DownloadLauncher::_ToDownloadFileState()
	{
		const auto filePath = _DownloadList.front();

		Utility::File::CreateDir(filePath.parent_path());

		const auto url = Utility::DataDefine::FilePathToUrl(filePath);
		const auto facade = _DownloadProvider.Start(url);

		Utility::File::FileWriter fileWriter(filePath.string(),"wb");

		auto dfs = new State::DownloadFileState(facade, fileWriter);

		dfs->Enter();

		dfs->OnProgressEvent([=](int total_size, int downloaded_size)
		{
			_OnProgress(total_size, downloaded_size);
		});

		dfs->OnDoneEvent([&]()
		{
			_DownloadList.pop();

			if (_DownloadList.empty())
			{
				_ToUnZip();
			}
			else
			{
				_ToDownloadFileState();
			}
		});
	}

	void DownloadLauncher::_ToUnZip()
	{
		for(auto it : _FilePaths)
		{
			Utility::File::UnZipToDisk(it.second.string());

			const auto path = Utility::DataDefine::FileListSavePath(it.first);
			_ToParserFileListState(path);
		}
		
		_ToUpdteLocalVer();
		_RemoveDownloadPack();
		_OnSuccess();
	}

	void DownloadLauncher::_ToParserFileListState(const path& file_path)
	{
		const auto fileList = Utility::File::DataParser::ParserFileListByFile(file_path.string());

		_ToMerge(fileList, file_path);
	}

	void DownloadLauncher::_ToMerge(const Utility::DataDefine::FileList& file_list, const path& file_path)
	{
		for(auto& file : file_list)
		{
			if(file.StateSymbol =="+")
			{
				copy(file_path.parent_path(), Utility::DataDefine::RESOURCE_FOLDER_NAME, copy_options::update_existing);

				//copy file to resource floder
			}
			else if(file.StateSymbol == "-")
			{
				remove(Utility::DataDefine::LocalVerSavePath());

				//remove file to resource floder
			}  
		}
	}

	void DownloadLauncher::_ToUpdteLocalVer()
	{
		remove(Utility::DataDefine::LocalVerSavePath());
		rename(Utility::DataDefine::NewestVerSavePath(), Utility::DataDefine::LocalVerSavePath());
	}

	void DownloadLauncher::_RemoveDownloadPack()
	{
		remove_all(Utility::DataDefine::PACKING_FOLDER_NAME);
	}

	void DownloadLauncher::OnDownloadProgress(Utility::DataDefine::OnProgress&& callback)
	{
		_OnProgress = callback;
	}

	void DownloadLauncher::OnUpdateSuccessEvent(Utility::DataDefine::OnSuccess&& callback)
	{
		_OnSuccess = callback;
	}

	void DownloadLauncher::OnNotNeedEvent(Utility::DataDefine::OnNotNeed&& callback)
	{
		_OnNotNeed = callback;
	}
}
