#include "TileType.h"
#include <Arduboy2.h>
Arduboy2 arduboy;
#include "GameSprites.h"

// Changes to make:
// - Create pause function on B button press and call drawMap function in it
// - Create functions toIso and toCart to go to and from Isometric/Cartesian
// - Draw new map tiles using toIso (and probably an enum due to how theyre stored in memory?)


class Vector {
  public:
    float x = 0;
    float y = 0;
};

// The game camera, represented by the camera's top left coordinates
Vector camera;

// The dimensions of the screen
constexpr uint8_t screen_height = HEIGHT;
constexpr uint8_t screen_width = WIDTH;

// The centre coordinates of the screen
constexpr uint8_t viewport_center_height = screen_height / 2;
constexpr uint8_t viewport_center_width = screen_width / 2;

// The dimensions of the tiles
constexpr uint8_t tileWidth = 19;
constexpr uint8_t tileHeight = 9;

// The dimensions of the map
constexpr uint8_t mapHeight = 32;
constexpr uint8_t mapWidth = 32;

// A 2D array of tiles, represented with 'TileType'
TileType tileMap[mapHeight][mapWidth] {};

inline uint8_t getSpriteHeight(const uint8_t * sprite)
{
  return pgm_read_byte(&sprite[1]);
}

inline uint8_t getSpriteWidth(const uint8_t * sprite)
{
  return pgm_read_byte(&sprite[0]);
}

TileType generateRandomTile()
{
  constexpr uint8_t tileMin = toTileIndex(TileType::building0);
  constexpr uint8_t tileMax = toTileIndex(TileType::blankTile);
  ////Not inclusive, add 1
  return fromTileIndex(random(tileMin, tileMax + 1));
}

/*
-It starts with the whole rectangular map filled with houses
-Then it picks a random position along the X axis and draws a vertical line of road tiles at that X coordinate from top to bottom (this is a ‘vertical step’).
//Instead of placing the partition completely randomly, it may be better of have the parition occur randomly up to ‘N’ tiles away from the centre of the area. 
//E.g. up to 3 tiles away from the centre, so you could end up with anything from -3 to +3 tiles away from the centre, where permitted.
//You’d need to calculate the centre first, which is probably something like y + ((height - 2) / 2) and x + ((width - 2) / 2), 
//then calculate a random offset between -n and +n, which is probably something like rand(n * 2) - n, then add them together.
-Then it considers the building tiles to the left of that road/partition line to be one rectangular space 
and the building tiles to the right of that road/partition line to be a second rectangular space.
-On each rectangular partition it performs a ‘horizontal step’, which is the same thing as a ‘vertical step’, 
except the road/partition line is drawn along the X axis from left to right (i.e. the random value is chosen along the Y axis). 
This also causes a partition, which means there are then effectively 4 rectangular building zones.
-More vertical and horizontal steps are performed repeatedly until either a certain ‘depth’ of partitioning steps 
or the rectangular partition is smaller than a particular size.
*/

void fill()
{
  for(size_t y = 0; y < 32; ++y)
    for(size_t x = 0; x < 32; ++x)
      tileMap[y][x] = generateRandomTile();
}

void fillHorizontalLine(uint8_t x, uint8_t y, uint8_t width, TileType tileType)
{
  for(size_t offset = 0; offset < width; ++offset)
    if(x + offset < 32)
      tileMap[y][x + offset] = tileType;
}

void fillVerticalLine(uint8_t x, uint8_t y, uint8_t height, TileType tileType)
{
  for(size_t offset = 0; offset < height; ++offset)
    if(y + offset < 32)
      tileMap[y + offset][x] = tileType;
}

void generateHorizontalStep(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t depth);
void generateVerticalStep(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t depth);

void generateSubdivide(uint8_t depth)
{
  fill();
  generateVerticalStep(0, 0, 32, 32, depth);
}

void generateHorizontalStep(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t depth)
{
  if(depth == 0)
    return;

  if(width < 2)
    return;

  if(height < 3)
    return;
  //const uint8_t division = 1 + (rand() % height - 2) is what picks the offset at which to divide the Y plane.
  const uint8_t division = 1 + (rand() % (height - 2));

  fillHorizontalLine(x, y + division, width, TileType::roadTile);

  const uint8_t upperY = y;
  const uint8_t upperHeight = division;

  const uint8_t lowerY = (y + division + 1);
  const uint8_t lowerHeight = (height - division - 1);

  generateVerticalStep(x, upperY, width, upperHeight, depth - 1);
  generateVerticalStep(x, lowerY, width, lowerHeight, depth - 1);
}

void generateVerticalStep(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t depth)
{
  if(depth == 0)
    return;

  if(height < 2)
    return;

  if(width < 3)
    return;
  //const uint8_t division = 1 + (rand() % width - 2) is what picks the offset at which to divide the X plane
  const uint8_t division = 1 + (rand() % (width - 2));

  fillVerticalLine(x + division, y, height, TileType::roadTile);

  const uint8_t leftX = x;
  const uint8_t leftWidth = division;

  const uint8_t rightX = (x + division + 1);
  const uint8_t rightWidth = (width - division - 1);

  generateHorizontalStep(leftX, y, leftWidth, height, depth - 1);
  generateHorizontalStep(rightX, y, rightWidth, height, depth - 1);
}

void drawMiniMap()
{
  for (uint8_t y = 0; y < mapHeight; ++y)
  {
    // Calculate the y position to draw the tile at, 6 is tile height
    int16_t drawY = ((y * 6) - camera.y);

    for (uint8_t x = 0; x < mapWidth; ++x)
    {
      // Calculate the x position to draw the tile at, 6 is tile width:
      int16_t drawX = ((x * 6) - camera.x);

      // Read the tile from the map.
      TileType tileType = tileMap[y][x];

      // Figure out the tile index.
      uint8_t tileIndex = toTileIndex(tileType);

      // Draw the tile at the calculated position.
      Sprites::drawOverwrite(drawX, drawY, minimapTileSprites, tileIndex);
    }
  }
}

// Isometric map tiles
constexpr uint8_t const * tileSprites[]
{
  building0,
  building1,
  building2,
  building3,
  blankTile,
  roadTiles,
};

constexpr uint8_t const * tileMasks[]
{
  building0_mask,
  building1_mask,
  building2_mask,
  building3_mask,
};

void drawIsoMap()
{
  for (uint8_t tileY = 0; tileY < mapHeight; ++tileY)
  {
    for (uint8_t tileX = 0; tileX < mapWidth; ++tileX)
    {
      // Calculate the x position to draw the tile at.
      const int16_t isometricX = (((tileX * tileWidth) / 2) - ((tileY * tileWidth) / 2));
      const int16_t drawX = (isometricX - camera.x);

      // Calculate the y position to draw the tile at.
      const int16_t isometricY = (((tileX * tileHeight) / 2) + ((tileY * tileHeight) / 2));
      const int16_t drawY = (isometricY - camera.y);

      // TODO: Skip off-screen tiles

      // Read the tile from the map.
      const TileType tileType = tileMap[tileY][tileX];

      // Figure out the tile index.
      const uint8_t tileIndex = toTileIndex(tileType);

      // Select the building sprite
      const uint8_t * tileSprite = tileSprites[tileIndex];

      // Select the building sprite mask
      const uint8_t * tileMask = tileMasks[tileIndex];

      // Get the sprite's height
      const uint8_t spriteHeight = getSpriteHeight(tileSprite);

      // Adjust the y position to account for the height of the sprite
      const int16_t adjustedY = (drawY - (spriteHeight - tileHeight));

      // Draw the tile at the calculated position.
      Sprites::drawExternalMask(drawX, adjustedY, tileSprite, tileMask, 0, 0);
    }
  }
}