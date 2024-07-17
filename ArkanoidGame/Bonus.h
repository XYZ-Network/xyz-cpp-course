#pragma once
#include <functional>

class Bonus
{
public:
	Bonus(std::function<void()>&& bonusActivate, std::function<void()>&& bonusDeactivate, float bonusDuration);

	void Activate();
	void Update(float timeDelta);

private:
	void Deactivate();

	std::function<void()> activation = []() {};
	std::function<void()> deactivation = []() {};
	float duration = 0;
	float curentActiveTime = 0;
	bool isActive = false;
};

