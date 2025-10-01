#include "Tile.hpp"

Tile::Tile(int id, sf::Texture& texture, sf::Vector2u tileSize, bool isCollidable) : sprite(texture), collidable(isCollidable)
{
    this->id = id;

    sprite.setTexture(texture);

    texture.setSmooth(false);

    int tilesPerRow = texture.getSize().x / tileSize.x;

    sprite.setTextureRect(sf::IntRect({
        (id % tilesPerRow) * static_cast<int>(tileSize.x),
        (id / tilesPerRow)* static_cast<int>(tileSize.y) }, {
        static_cast<int>(tileSize.x),
        static_cast<int>(tileSize.y) }
    ));
  
   

}

void Tile::draw(sf::RenderWindow& window) {
    window.draw(sprite);

   if (isLedge) {
        sf::RectangleShape box;
        box.setPosition({ ledgeGrabBox.position.x, ledgeGrabBox.position.y });
        box.setSize({ ledgeGrabBox.size.x, ledgeGrabBox.size.y });
        box.setFillColor(sf::Color(255, 255, 0, 100));
        box.setOutlineColor(sf::Color::Red);
        box.setOutlineThickness(1.f);

       // std::cout << "DRAWN" << std::endl;

      
       // window.draw(box);
    }
}

const sf::FloatRect Tile::getBounds() const {
    return sprite.getGlobalBounds();
}

bool Tile::isCollidableTile() const {
    return collidable;
}

sf::Sprite& Tile::getSprite()
{
    return this->sprite;
}

void Tile::drawCollisionBox(sf::RenderWindow& window) {
    // Get the tile's collision box
    sf::FloatRect bounds = this->getBounds();

    // Create a rectangle shape for the collision box
    sf::RectangleShape collisionBox(sf::Vector2f(bounds.size.x, bounds.size.y));

    // Set the position of the collision box to match the tile's sprite
    collisionBox.setPosition({ bounds.position.x, bounds.position.y });

    // Set a color to make the collision box visible
    collisionBox.setFillColor(sf::Color(0, 0, 255, 128)); // Semi-transparent blue

    // Draw collision box
    window.draw(collisionBox);
}

int Tile::getID()
{
    return this->id;
}
