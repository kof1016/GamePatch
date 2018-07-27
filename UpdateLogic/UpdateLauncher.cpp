#include "UpdateLauncher.h"
#include "State/DownloadFileState.h"
#include "State/ParserFilelistState.h"
#include "State/FindDiffState.h"
#include <filesystem>
#include <iostream>
#include "../Utility/File/FileTool.h"
#include "../Utility/File/DataParser.h"

namespace UpdateLogic
{
	UpdateLauncher::UpdateLauncher()
	{
	}


	UpdateLauncher::~UpdateLauncher()
	{
	}

	void UpdateLauncher::Start()
	{
		FileTool::CreateDir(Utility::PACKING_FOLDER_NAME);

		_ToDownloadNewestVer();
	}

	void UpdateLauncher::_ToDownloadNewestVer()
	{
		path filePath = Utility::NewestVerSavePath();;
		const auto url = Utility::FilePathToUrl(filePath);
		const auto facade = _DownloadProvider.Start(url);
		Utility::FileWriter fileWriter(filePath.string(),"w");

		auto dfs = new DownloadFileState(facade, fileWriter);
		
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

	void UpdateLauncher::_ToParserVerNumberState(path file_path)
	{
		const auto newestVer = Utility::DataParser::ParserVersionNumberByFile(file_path.string());

		const auto localVer = Utility::DataParser::ParserVersionNumberByFile(Utility::LocalVerSavePath().string());

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

	void UpdateLauncher::_ToDiffVerNumberState(int local_ver, int newest_ver)
	{
		for (int i = local_ver + 1; i <= newest_ver; ++i)
		{
			auto path = Utility::ZipFileSavePath(i);
			_DownloadList.emplace(path);
			_FilePaths.emplace(i, path);
		}
		
		_ToDownloadFileState();
	}

	void UpdateLauncher::_ToDownloadFileState()
	{
		const auto filePath = _DownloadList.front();
		
		FileTool::CreateDir(filePath.parent_path());

		const auto url = Utility::FilePathToUrl(filePath);
		const auto facade = _DownloadProvider.Start(url);
		
		Utility::FileWriter fileWriter(filePath.string(),"wb");

		auto dfs = new DownloadFileState(facade, fileWriter);

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

	void UpdateLauncher::_ToUnZip()
	{
		for(auto it : _FilePaths)
		{
			FileTool::UnZipToDisk(it.second.string());

			const auto path = Utility::FileListSavePath(it.first);
			_ToParserFileListState(path);
		}
		
		_ToUpdteLocalVer();
		_RemoveDownloadPack();
		_OnSuccess();
	}

	void UpdateLauncher::_ToParserFileListState(const path& file_path)
	{
		const auto fileList = Utility::DataParser::ParserFileListByFile(file_path.string());

		_ToMerge(fileList, file_path);
	}

	void UpdateLauncher::_ToMerge(const Utility::FileList& file_list, const path& file_path)
	{
		for(auto& file : file_list)
		{
			if(file.StateSymbol =="+")
			{
				copy(file_path.parent_path(), Utility::RESOURCE_FOLDER_NAME, copy_options::update_existing);

				//copy file to resource floder
			}
			else if(file.StateSymbol == "-")
			{
				remove(Utility::LocalVerSavePath());

				//remove file to resource floder
			}  
		}
	}

	void UpdateLauncher::_ToUpdteLocalVer()
	{
		remove(Utility::LocalVerSavePath());
		rename(Utility::NewestVerSavePath(), Utility::LocalVerSavePath());
	}

	void UpdateLauncher::_RemoveDownloadPack()
	{
		remove_all(Utility::PACKING_FOLDER_NAME);
	}

	void UpdateLauncher::OnDownloadProgress(Utility::OnProgress&& callback)
	{
		_OnProgress = callback;
	}

	void UpdateLauncher::OnUpdateSuccessEvent(Utility::OnSuccess&& callback)
	{
		_OnSuccess = callback;
	}

	void UpdateLauncher::OnNotNeedEvent(Utility::OnNotNeed&& callback)
	{
		_OnNotNeed = callback;
	}
}
