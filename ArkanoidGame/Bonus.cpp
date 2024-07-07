#include "Bonus.h"

Bonus::Bonus(std::function<void()>&& bonusActivate, std::function<void()>&& bonusDeactivate, float bonusDuration) :
	activation(std::move(bonusActivate)),
	deactivation(std::move(bonusDeactivate)),
	duration(bonusDuration)
{
}

void Bonus::Activate()
{
	isActive = true;
	if (activation)
		activation();
}

void Bonus::Update(float timeDelta)
{
	if (!isActive)
		return;
	curentActiveTime += timeDelta;

	if (curentActiveTime >= duration)
	{
		Deactivate();
	}
}

void Bonus::Deactivate()
{
	isActive = false;
	curentActiveTime = 0;
	if (deactivation)
		deactivation();
}

