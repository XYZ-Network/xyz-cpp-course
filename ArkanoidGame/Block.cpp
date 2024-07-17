#include "Block.h"
#include "Sprite.h"
#include "GameSettings.h"

#include <assert.h>

namespace
{
	const std::string TEXTURE_ID = "platform";
}

namespace ArkanoidGame
{
	Block::Block(const sf::Vector2f& position, const sf::Color& color)
		: GameObject(SETTINGS.TEXTURES_PATH + TEXTURE_ID + ".png", position, SETTINGS.BLOCK_WIDTH, SETTINGS.BLOCK_HEIGHT)
	{
		sprite.setColor(color);
	}

	bool Block::GetCollision(std::shared_ptr<Colladiable> collidableObject) const {
		auto gameObject = std::dynamic_pointer_cast<GameObject>(collidableObject);
		assert(gameObject);
		sf::Rect rect = gameObject->GetRect();
		rect.width *= 1.1;
		return GetRect().intersects(gameObject->GetRect());
	}

	void Block::OnHit()
	{
		hitCount = 0;
		Emit();
	}

	bool Block::IsBroken()
	{
		return hitCount <= 0;
	}

	void Block::Update(float timeDelta)
	{

	}

	Block::~Block() {

	}
	


	SmoothDestroyableBlock::SmoothDestroyableBlock(const sf::Vector2f& position, const sf::Color& color)
		: Block(position, color)
		, color(color)

	{
	}



	void SmoothDestroyableBlock::Update(float timeDelta)
	{
		UpdateTimer(timeDelta);
	}

	bool SmoothDestroyableBlock::GetCollision(std::shared_ptr<Colladiable> collidableObject) const {
		if (isTimerStarted_) {
			return false;
		}

		auto gameObject = std::dynamic_pointer_cast<GameObject>(collidableObject);
		assert(gameObject);
		sf::Rect rect = gameObject->GetRect();
		rect.width *= 1.1f;
		return GetRect().intersects(gameObject->GetRect());
	}

	void SmoothDestroyableBlock::OnHit()
	{
		StartTimer(SETTINGS.BREAK_DELAY);
	}

	void SmoothDestroyableBlock::FinalAction()
	{
		--hitCount;
		Emit();
	}

	void SmoothDestroyableBlock::EachTickAction(float deltaTime)
	{
		color.a = 255 * currentTime_ / destroyTime_;
		sprite.setColor(color);
	}

	UnbreackableBlock::UnbreackableBlock(const sf::Vector2f& position)
		: Block(position, sf::Color::Color(105, 105, 105))
	{	}

	void UnbreackableBlock::OnHit() {
		//--hit_count ;
	}
}