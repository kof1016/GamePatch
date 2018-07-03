#include "UpdateLauncher.h"
#include "DownloadFileState.h"
#include "ParserFilelistState.h"
#include "FindDiffState.h"
#include "DataDefine.h"
#include <filesystem>
#include <iostream>
#include "../Utility/FileTool.h"
#include "../Utility/DataParser.h"

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
		path filePath = Utility::PACKING_FOLDER_NAME / Utility::NEWESTVER_NAME;
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
		_NewestVer = Utility::DataParser::ParserVersionNumberByFile(file_path.string());

		_LocalVer = Utility::DataParser::ParserVersionNumberByFile(Utility::LocalVerSavePath().string());

		if(_LocalVer ==_NewestVer)
		{
			std::cout << "local ver = newestver, into game" << std::endl;
		}
		else
		{
			_ToDiffVerNumberState();
		}
	}

	void UpdateLauncher::_ToDiffVerNumberState()
	{
		for (int i = _LocalVer + 1; i <= _NewestVer; ++i)
		{
			auto path = Utility::ZipFileSavePath(i);
			_FilePaths.emplace(path);
		}

		_FilePathTmp = _FilePaths;
		
		_ToDownloadFileState();
	}

	void UpdateLauncher::_ToDownloadFileState()
	{
		const auto filePath = _FilePaths.front();
		
		FileTool::CreateDir(filePath.parent_path());


		const auto url = Utility::FilePathToUrl(filePath);
		const auto facade = _DownloadProvider.Start(url);
		//Utility::FileWriter fileWriter(filePath.string());
		Utility::FileWriter fileWriter(filePath.string(),"wb");


		auto dfs = new DownloadFileState(facade, fileWriter);
		dfs->Enter();

		dfs->OnProgressEvent([=](int total_size, int downloaded_size)
		{
			_OnProgress(total_size, downloaded_size);
		});

		dfs->OnDoneEvent([&]()
		{
			_FilePaths.pop();

			if (_FilePaths.empty())
			{
				_ToUnZip();
			}
			else
			{
				_ToDownloadFileState();
			}
		});

		// const std::shared_ptr<Utility::IState> state(dfs);
		// _StateMachine.Push(state);
	}

	void UpdateLauncher::_ToUnZip()
	{
		//unzipfile
		while(!_FilePathTmp.empty())
		{
			const auto zipFilePath = _FilePathTmp.front();

			_ToParserFilelistState(zipFilePath);
			_FilePathTmp.pop();
		}

		_ToUpdteLocalVer();
	}

	void UpdateLauncher::_ToParserFilelistState(path file_path)
	{
		//auto fileList = Utility::DataParser::ParserFileList(file_path.parent_path().string());
		auto fileList = Utility::DataParser::ParserFileListByFile(file_path.string());

		_ToMerge(fileList, file_path);
	
	}

	void UpdateLauncher::_ToMerge(Utility::FileList file_list, path file_path)
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
		Utility::LocalVerSavePath();
		remove(Utility::LocalVerSavePath());
		rename(Utility::NewestVerSavePath(), Utility::LocalVerSavePath());
	}

	void UpdateLauncher::Update()
	{
		//_StateMachine.Update();
	}

	void UpdateLauncher::Shutdown()
	{
		std::cout << "UpdateLauncher::Shutdown" << std::endl;
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
