#pragma once
#include "Animation.hpp"
#include <vector>

//namespace TILEMAP
//{
//	enum class TileType
//	{
//		Default = 0,
//		Wall = 1,
//		newLevel = 2,
//		Entity_Spawn_Position = 3,
//		Player_SpawnPoint = 4,
//		Path_Finding = 5,
//		Invisible_Wall = 6,
//
//	};
//	class Tile
//	{
//
//	public:
//
//		Tile(const sf::Vector2f tile_position, const sf::Texture& tileTexture, const sf::IntRect& tileIntRect, const std::string doorName, const TILEMAP::TileType tileType = TileType::Default, const short unsigned tileRotation = 0);
//
//		//GETTERS
//		const sf::Sprite getSprite() const;
//		const std::string getDoorName() const;
//		const sf::Vector2f getTilePosition() const;
//		const TileType getTileType() const;
//		const std::string getTileMapInfo() const;
//
//		//RENDER FUNCTIONS
//		void render(sf::RenderTarget& target);
//
//		//virtual ~Tile();
//
//	private:
//
//		sf::Sprite tileSprite;
//		short unsigned tileRotation;
//		std::string doorName;
//		TileType tileType;
//		
//		void initVariables(const sf::Vector2f tile_position, const sf::Texture& tileTexture, const sf::IntRect& tileIntRect, const std::string doorName = "NULL", const TILEMAP::TileType tileType = TileType::Default, const short unsigned tileRotation = 0);
//
//	};
//
//	class TileMap
//	{
//	public:
//
//		TileMap(float tileSize, sf::Vector2u mapSize, std::string filePath);
//
//		~TileMap();
//
//		//ADD AND REMOVE TILES
//		void addTile(const unsigned tile_layer, const sf::Vector2u tilePosition, const unsigned tileRotation, const std::string doorName, const TILEMAP::TileType tileType);
//
//		void removeTile(const unsigned tile_layer, const sf::Vector2u tilePosition);
//
//	private:
//		float tileSize;
//		unsigned tileLayers;
//		sf::Vector2u mapSize;
//		std::vector<std::vector<std::vector<std::unique_ptr<TILEMAP::Tile>>>> tileMap;
//		std::string filePath;
//		sf::Texture texture;
//		sf::IntRect textureIntRect;
//
//		void initVariables(float tileSize, sf::Vector2u mapSize, std::string filePath);
//	};
//
//};