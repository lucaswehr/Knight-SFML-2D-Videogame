#pragma once
#include "Animation.hpp"

class Healthbar
{
public:

	sf::RectangleShape healthBar;
	sf::RectangleShape backgroundBar;

	float displayedHealth = 100.f;

	Healthbar(float x, float y)
	{
		healthBar.setFillColor(sf::Color::Red);
		healthBar.setOutlineColor(sf::Color::Black);
		healthBar.setOutlineThickness(5);

		backgroundBar.setSize({ x, y });
		backgroundBar.setFillColor(sf::Color::Black);
		
	}
	
	void update(float deltaTime, float actualHealth, float maxHealth, float posX, float posY)
	{
		float speed = 200.f; 
		if (displayedHealth > actualHealth)
		{
			displayedHealth -= speed * deltaTime;
			if (displayedHealth < actualHealth)
				displayedHealth = actualHealth;
		}
		else if (displayedHealth < actualHealth)
		{
			displayedHealth += speed * deltaTime;
			if (displayedHealth > actualHealth)
				displayedHealth = actualHealth;
		}

		float ratio = displayedHealth / maxHealth;
		ratio = std::clamp(ratio, 0.f, 1.f);


		float newWidth = backgroundBar.getSize().x * ratio;
		healthBar.setSize({ newWidth, backgroundBar.getSize().y });
		healthBar.setPosition({posX,posY});
		backgroundBar.setPosition({posX,posY});

	}
	
	void draw(sf::RenderWindow& window)
	{
		window.draw(backgroundBar);
		window.draw(healthBar);
	}

};
