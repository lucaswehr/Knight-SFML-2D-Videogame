#pragma once
#include "Animation.hpp"
#include <vector>


class Tile
{

public:
    Tile(int id, sf::Texture& texture, sf::Vector2u tileSize, bool isCollidable);

    void draw(sf::RenderWindow& window);
    const sf::FloatRect getBounds() const;
    bool isCollidableTile() const;
    sf::Sprite& getSprite();
    void drawCollisionBox(sf::RenderWindow& window);

    int getID();

    sf::FloatRect ledgeGrabBox;
    bool isLedge = false;
    sf::RectangleShape debugLedgeBox;

private:

    sf::Sprite sprite;
    bool collidable;
    int id;

};


