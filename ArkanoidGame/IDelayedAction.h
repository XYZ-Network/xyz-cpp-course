#pragma once
#include "SFML/Graphics.hpp"
#include <memory>

namespace ArkanoidGame
{
	class IDelayedAction
	{
	protected:
		bool isTimerStarted_ = false;
		float destroyTime_ = 0;
		float currentTime_ = 0;

		virtual void UpdateTimer(float deltaTime) {
			if (!isTimerStarted_)
				return;
			currentTime_ -= deltaTime;
			EachTickAction(deltaTime);
			if (currentTime_ <= 0)
			{
				FinalAction();
				isTimerStarted_ = false;
			}
		}

		virtual void FinalAction() = 0;
		virtual void EachTickAction(float deltaTime) = 0;
	public:
		void StartTimer(float destroyTime)
		{
			destroyTime_ = destroyTime;
			currentTime_ = destroyTime;
			isTimerStarted_ = true;
		}
	};

}