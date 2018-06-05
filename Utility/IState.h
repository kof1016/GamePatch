#pragma once
namespace Utility
{
	class IState
	{
	public:
		virtual ~IState() = default;
		virtual void Enter() =0;

		virtual void Leave() =0;

		virtual void Update() =0;
	};
}
