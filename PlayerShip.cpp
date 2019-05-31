#include "PlayerShip.hpp"
#include "DEFINITIONS.hpp"

namespace rstar
{
	PlayerShip::PlayerShip(GameDataPtr data, sf::Clock &clockRef)
		: GameObject(data), clockRef_(clockRef)
	{
		sprite_.setTexture(data_->assets.GetTexture("Player Ship"));
		sprite_.setScale(2.f, 2.f);
		sprite_.setPosition(static_cast<float>(WINDOW_WIDTH) / 2.f - GetBounds().width / 2.f, static_cast<float>(WINDOW_HEIGHT) - GetBounds().height * 2.f);
	}

	PlayerShip::PlayerShip(GameDataPtr data, sf::Clock &clockRef, int lives, int score, float movementSpeed, float bulletsSpeed)
		: GameObject(data), clockRef_(clockRef), lives_(lives), score_(score), movementSpeed_(movementSpeed), bulletsSpeed_(bulletsSpeed)
	{
		sprite_.setTexture(data_->assets.GetTexture("Player Ship"));
		sprite_.setScale(2.f, 2.f);
		sprite_.setPosition(static_cast<float>(WINDOW_WIDTH) / 2.f - GetBounds().width / 2.f, static_cast<float>(WINDOW_HEIGHT) - GetBounds().height * 2.f);
	}


	void PlayerShip::Shoot()
	{
		bullet_ = std::make_unique<Bullet>(data_, sf::Vector2f{ GetPosition().x + GetBounds().width / 2.f, GetPosition().y }, bulletsSpeed_, true);
	}

	void PlayerShip::Update()
	{
		if (lives_ != 0)
		{
			if (hit_)
			{
				animateHit();
			}
			handleMovement();
			handleShooting();
		}
	}

	void PlayerShip::animateHit()
	{
		if (clockRef_.getElapsedTime().asSeconds() - animationTimeOffset_ > PLAYER_BLURRING_FRAME_TIME)
		{
			if (currentHitTexture_ % 2 == 0)
			{
				sprite_.setTexture(data_->assets.GetTexture("Hit Player Ship"));
			}
			else
			{
				sprite_.setTexture(data_->assets.GetTexture("Player Ship"));
			}

			if (currentHitTexture_ < PLAYER_BLURRING_FRAMES)
			{
				++currentHitTexture_;
				animationTimeOffset_ = clockRef_.getElapsedTime().asSeconds();
			}
			else
			{
				hit_ = false;
				sprite_.setTexture(data_->assets.GetTexture("Player Ship"));
				currentHitTexture_ = 0;
				animationTimeOffset_ = 0.f;
			}
		}
	}

	void PlayerShip::Draw() const
	{
		data_->window.draw(sprite_);
		if (bullet_)
		{
			bullet_->Draw();
		}
	}

	void PlayerShip::handleMovement()
	{
		sf::Vector2f moveDirection{0,0};

		// if A or Left arrow is pressed change movement vector.x to negative value
		if ( (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && GetPosition().x > 0 )
		{
			moveDirection.x = -movementSpeed_;
		}

		// if D or Right arrow is pressed change movement vector.x to positive value
		if ( (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && GetPosition().x + GetBounds().width < WINDOW_WIDTH )
		{
			moveDirection.x = movementSpeed_;
		}

		sprite_.move(moveDirection);
	}

	void PlayerShip::handleShooting()
	{
		// if space is pressed shoot
		if (!bullet_ &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			Shoot();
		}

		if (bullet_)
		{
			if (bullet_->IsOutOfScreen())
			{
				bullet_.reset(nullptr);
			}
			else
			{
				bullet_->Update();
			}
		}

	}
}
