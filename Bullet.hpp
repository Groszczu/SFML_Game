#pragma once
#include "GameObject.hpp"
#include "Game.hpp"
#include "DEFINITIONS.hpp"

namespace rstar
{
		// class to inherit from
	// derived class inherits protected class Bullet as its member
	// [this allows to reuse Bullet class in many classes]
	class BaseBullet
	{
	protected:
		class Bullet : public GameObject
		{
		public:
			Bullet(GameDataPtr data, sf::Texture const&, sf::Vector2f startPosition,
				float movementSpeed, DirectionX directionX = DirectionX::none, DirectionY directionY = DirectionY::down);

			void Update() override;
			void Draw() const override;

		private:
			float movementSpeed_;
			DirectionX directionX_;
			DirectionY directionY_;
		};
	};
}
