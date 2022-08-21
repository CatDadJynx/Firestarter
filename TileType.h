#pragma once

// For uint8_t
#include <stdint.h>

//Add blank and road tile types to isometric and mini map views

// Represents different tile types
enum class TileType : uint8_t
{
  building0,
  building1,
  building2,
  building3,
  //blankTile,
  blankTile0,
  blankTile1,
  roadTile,
};

// The number of valid tile types.
// Note: Be sure to manually update this
// when introducing new tile types.
//constexpr uint8_t tileCount = 6;
constexpr uint8_t tileCount = 7;

// Gets a tile type from its corresponding sprite index
inline constexpr TileType fromTileIndex(uint8_t tileIndex)
{
  // The basic implementation acquires a valid tile type from
  // its raw integer representation, using modular arithmetic
  // to ensure that the produced value is valid.
  return static_cast<TileType>(tileIndex  % tileCount);
}

// Gets the sprite index from the tile type.
inline constexpr uint8_t toTileIndex(TileType tileType)
{
  // The basic implementation just converts the
  // tile type to its underlying integer representation.
  return static_cast<uint8_t>(tileType);
}

/*
inline bool isWalkable(Tile tile)
{
  switch(tile)
  {
    // Add cases for every
    // kind of 'walkable' tile
    case Tile::BlankTile:
    case Tile::RoadTile:
      return true;
      
    // Assume anything that isn't in
    // the above case list is not walkable
    default:
      return false;
  }
}
*/
