#include "Tilemap.hpp"


//
//TILEMAP::Tile::Tile(const sf::Vector2f tile_position, const sf::Texture& tileTexture, const sf::IntRect& tileIntRect, const std::string doorName, const TILEMAP::TileType tileType, short unsigned tileRotation) :  tileSprite(tileTexture)
//{
//	this->initVariables(tile_position, tileTexture, tileIntRect, doorName, tileType, tileRotation);
//}
//
//const sf::Sprite TILEMAP::Tile::getSprite() const
//{
//	return this->tileSprite;
//}
//
//const std::string TILEMAP::Tile::getDoorName() const
//{
//	return this->doorName;
//}
//
//const sf::Vector2f TILEMAP::Tile::getTilePosition() const
//{
//	return this->tileSprite.getPosition();
//}
//
//const TILEMAP::TileType TILEMAP::Tile::getTileType() const
//{
//	return this->tileType;
//}
//
//const std::string TILEMAP::Tile::getTileMapInfo() const
//{
//	std::stringstream ss;
//
//	ss << this->tileSprite.getTextureRect().position.x << " " 
//		<< this->tileSprite.getTextureRect().position.y 
//		<< " " << static_cast<int>(this->tileType) << " " 
//		<< this->doorName << this->tileRotation;
//
//	return ss.str();
//}
//
//void TILEMAP::Tile::render(sf::RenderTarget& target)
//{
//	target.draw(this->tileSprite);
//}
//
//void TILEMAP::Tile::initVariables(sf::Vector2f tile_position, const sf::Texture& tileTexture, const sf::IntRect& tileIntRect, std::string doorName, TILEMAP::TileType tileType, short unsigned tileRotation)
//{
//	this->tileSprite.setPosition({ std::floor(tile_position.x), std::floor(tile_position.y) });
//	this->tileSprite.setTexture(tileTexture);
//	this->tileSprite.setTextureRect(tileIntRect);
//	this->doorName = doorName;
//	this->tileType = tileType;
//	this->tileSprite.setRotation(sf::degrees(tileRotation));
//}
//
//TILEMAP::TileMap::TileMap(float tileSize, sf::Vector2u mapSize, std::string filePath)
//{
//	this->initVariables(tileSize, mapSize, filePath);
//}
//
//TILEMAP::TileMap::~TileMap()
//{ 
//
//}
//
//void TILEMAP::TileMap::addTile(const unsigned tile_layer, const sf::Vector2u tilePosition, const unsigned tileRotation, const std::string doorName, const TILEMAP::TileType tileType)
//{
//	if (tile_layer < this->tileLayers && tile_layer >= 0 && tilePosition.x < this->mapSize.x && tilePosition.x >= 0 && tilePosition.y < this->mapSize.y && tilePosition.y >= 0)
//	{
//		if (this->tileMap[tile_layer][tilePosition.x][tilePosition.y] == nullptr)
//		{
//			sf::IntRect rect({ textureIntRect.size.x,textureIntRect.size.y }, { static_cast<int>(std::floor(tileSize)), static_cast<int>(std::floor(tileSize))});
//			
//			this->tileMap[tile_layer][tilePosition.x][tilePosition.y] = std::make_unique<TILEMAP::Tile>(
//				sf::Vector2f(std::floor(static_cast<float>(tilePosition.x)), std::floor(static_cast<float>(tilePosition.y))),
//				this->texture,
//				rect,
//				doorName,
//				tileType,
//				tileRotation
//			);
//				
//		}
//	}
//}
//
//void TILEMAP::TileMap::removeTile(const unsigned tile_layer, const sf::Vector2u tilePosition)
//{
//	if (tile_layer < this->tileLayers && tile_layer >= 0 && tilePosition.x < this->mapSize.x && tilePosition.x >= 0 && tilePosition.y < this->mapSize.y && tilePosition.y >= 0)
//	{
//		if (this->tileMap[tile_layer][tilePosition.x][tilePosition.y] != nullptr)
//		{
//			this->tileMap[tile_layer][tilePosition.x][tilePosition.y].reset();
//		}
//	}
//}
//
//
//void TILEMAP::TileMap::initVariables(float tileSize, sf::Vector2u mapSize, std::string filePath)
//{
//	this->tileSize = tileSize;
//	this->mapSize = mapSize;
//	this->filePath = filePath;
//	this->textureIntRect = sf::IntRect({ 0,0 }, { static_cast<int>(tileSize), static_cast<int>(tileSize) });
//	this->tileLayers = 10;
//
//	if (!texture.loadFromFile(filePath))
//	{
//		std::cout << "TILEMAP ERROR" << std::endl;
//	}
//
//	this->tileMap.resize(this->tileLayers);
//	for (size_t tile_layer = 0; tile_layer < this->tileLayers; tile_layer++)
//	{
//		this->tileMap[tile_layer].resize(this->mapSize.x);
//
//		for (size_t x = 0; x < mapSize.x; x++)
//		{
//			this->tileMap[tile_layer][x].resize(this->mapSize.y);
//		}
//	}
//}
