#pragma once

// For uint8_t
#include <stdint.h>

//Add blank and road tile types

// Represents different tile types
enum class TileType : uint8_t
{
  building0,
  building1,
  building2,
  building3,
};

// The number of valid tile types.
// Note: Be sure to manually update this
// when introducing new tile types.
constexpr uint8_t tileCount = 4;

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
