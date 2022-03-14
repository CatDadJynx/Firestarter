#include "TileType.h"
#include <Arduboy2.h>
Arduboy2 arduboy;
#include "GameSprites.h"

class Vector {
  public:
    float x = 0;
    float y = 0;
};

Vector camera;

//Appropriate data types?
const uint8_t screen_height = 64;
const uint8_t screen_width = 128;

const uint8_t viewport_center_height = screen_height / 2;
const uint8_t viewport_center_width = screen_width / 2;

const uint8_t mapHeight = 32;
const uint8_t mapWidth = 32;

// A 2D array of tile types/tile indices
//uint8_t world[world_height][world_width] { /* Fill the map data in as necessary */ };
TileType tileMap[mapHeight][mapWidth] {};

//World array?

//Coordinates to isomentric?

void generateMap()
{
  for(uint16_t tileY = 0; tileY < mapHeight; ++tileY)
    for(uint16_t tileX = 0; tileX < mapWidth; ++tileX)
      tileMap[tileY][tileX] = static_cast<TileType>(random() % 4);
}

void drawMap()
{
  for(uint8_t y = 0; y < mapHeight; ++y)
  {
    // Calculate the y position to draw the tile at, 6 is tile height
    int16_t drawY = ((y * 6) - camera.y);
    
    for(uint8_t x = 0; x < mapWidth; ++x)
    {
      // Calculate the x position to draw the tile at, 6 is tile width:
      int16_t drawX = ((x * 6) - camera.x);

      // Read the tile from the map.
      TileType tileType = tileMap[y][x];

      // Figure out the tile index.
      uint8_t tileIndex = toTileIndex(tileType);

      // Draw the tile at the calculated position.
      Sprites::drawOverwrite(drawX, drawY, buildingPlaceholders, tileIndex);
    }
  }
}
