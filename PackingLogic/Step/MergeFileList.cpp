#include "MergeFileList.h"
#include <utility>
#include "../../Utility/Linq/cpplinq.hpp"

namespace BZbee::Sandbox::GamePatch::PackingLogic::Step
{
	MergeFileList::MergeFileList(Utility::DataDefine::FileList current, Utility::DataDefine::FileList all_source)
		: _Current(std::move(current))
		, _AllSource(std::move(all_source))
	{
	}


	MergeFileList::~MergeFileList()
	{
	}

	Utility::DataDefine::FileList MergeFileList::Result()
	{
		using namespace cpplinq;

		const auto current = from(_Current)
			>> select([](auto d) { return d.MD5; })
			>> to_list();

		const auto source = from(_AllSource)
			>> select([](auto d) { return d.MD5; })
			>> to_list();

		const auto remove = from(current)
			>> except(from(source))
			>> to_list();


		const auto add = from(source)
			>> except(from(current))
			>> to_list();

		auto result = from(add)
			>> select([&](auto md5)
			{
				const auto r = std::find_if(_AllSource.begin(), _AllSource.end(),
											[&](auto& d)
											{
												if (md5 == d.MD5)
												{
													d.StateSymbol = "+";
												}

												return md5 == d.MD5;
											});
				return *r;
			})
			>> to_list();

		auto result2 = from(remove)
			>> select([&](auto key)
			{
				const auto r = std::find_if(_Current.begin(), _Current.end(),
											[&](auto& d)
											{
												if (key == d.MD5)
												{
													d.StateSymbol = "-";
												}

												return key == d.MD5;
											});
				return *r;
			})
			>> to_list();

		result.insert(result.end(), result2.begin(), result2.end());

		return result;
	}
}
