#pragma once

#include "Animation.hpp"

class Arrow 
{
public: 

	Arrow(sf::Texture& arrowTexture, sf::Vector2f startpos, sf::Vector2f direction, int gravityChange) : sprite(arrowTexture)
	{
		sprite.setPosition(startpos);
		sprite.setScale({ direction.x < 0.f ? -1.8f : 1.8f, 1.8f });
		sprite.setOrigin({ 20,64 });

		//int randomVelocity = std::rand() % 2000 + 1000;

		velocity = direction * 2000.f;

		arrowBox.setFillColor(sf::Color(255, 0, 0, 128));
		arrowBox.setSize({ 30.f,10.f });
		arrowBox.setScale({ 2,3 });

		int random = 0;

		if (gravityChange == 2)
		    random = 500+ std::rand() % 400; // 500-900
		else if (gravityChange == 1)
			random = std::rand() % 1000 + 2000; // 2000-3000

		std::cout << gravityChange << std::endl;

		gravity = random;
		

		if (direction.x < 0.f)
		arrowBox.setOrigin({ 42,30 });
		else if (direction.x > 0.f)
			arrowBox.setOrigin({ -13,30 });
		
		std::cout << "Arrow direction: " << direction.x << ", Sprite Scale: " << sprite.getScale().x
			<< ", Box Pos: " << arrowBox.getPosition().x << std::endl;
	}

	void update(float dt, std::vector<Arrow>& arrows, std::vector<Tile> tiles)
	{
		velocity.y += gravity * dt;

		arrowBox.setPosition(sprite.getPosition());

		sprite.move({ velocity.x * dt, 0 });

		if (!arrowGround)
		sprite.move({ 0, velocity.y * dt });

		for (auto& tile : tiles)
		{
			if (arrowBox.getGlobalBounds().findIntersection(tile.getBounds()))
			{
				sprite.move({ 0,0 });

				arrowGround = true;
			}

		}

		lifeTime -= dt;
	}

	bool isExpired()
	{
		return lifeTime <= 0.f;
	}
	
	sf::FloatRect getBounds()
	{
		return arrowBox.getGlobalBounds();
	}
	
	sf::Sprite getSprite()
	{
		return sprite;
	}

	void setArrowOnTile(bool value)
	{
		arrowOnTile = value;
	}

	bool getArrowOnTile()
	{
		return arrowOnTile;
	}

	bool arrowDirection()
	{
		return velocity.x > 0.f;
	}

	void setGravity(float value)
	{
		gravity = value;
	}

	sf::Vector2f velocity;

	sf::RectangleShape arrowBox;

	float lifeTime = 5.0f;

	sf::Sprite sprite;

	sf::RectangleShape debugBox;

private:

	//sf::Sprite sprite;

	bool arrowOnTile = false;

	float gravity = 200.f;

	bool arrowGround = false;

	//sf::Vector2f velocity;
	
};