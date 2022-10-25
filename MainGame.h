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

// Though it would be better to introduce a named function so you don’t forget what this code actually does:

inline uint8_t getSpriteHeight(const uint8_t * sprite)
{
  return pgm_read_byte(&sprite[1]);
}

inline uint8_t getSpriteWidth(const uint8_t * sprite)
{
  return pgm_read_byte(&sprite[0]);
}

//It starts with the whole rectangular map filled with houses
TileType generateRandomTile()
{
  constexpr uint8_t tileMin = toTileIndex(TileType::building0);
  constexpr uint8_t tileMax = toTileIndex(TileType::blankTile);
  //constexpr uint8_t tileMax = toTileIndex(TileType::blankTile1);
  ////Not inclusive, add 1
  return fromTileIndex(random(tileMin, tileMax + 1));
}

void fill()
{
  for(size_t y = 0; y < 32; ++y)
    for(size_t x = 0; x < 32; ++x)
      tileMap[y][x] = generateRandomTile();
}

//Then it picks a random position along the X axis and draws a horizontal line of road tiles at that X coordinate from top to bottom (this is a ‘horizontal step’).
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

//Then it considers the building tiles to the left of that road/partition line to be one rectangular space and the building tiles to the right of that road/partition line to be a second rectangular space.
void generateSubdivide(uint8_t depth)
{
  fill();
  generateVerticalStep(0, 0, 32, 32, depth);
}

//On each rectangular partition it performs a ‘horizontal step’, which is the same thing as a ‘vertical step’, except the road/partition line is drawn along the X axis from left to right (i.e. the random value is chosen along the Y axis). This also causes a partition, which means there are then effectively 4 rectangular building zones.
void generateHorizontalStep(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t depth)
{
  if(depth == 0)
    return;

  if(width < 2)
    return;

  if(height < 3)
    return;

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

  const uint8_t division = 1 + (rand() % (width - 2));

  fillVerticalLine(x + division, y, height, TileType::roadTile);

  const uint8_t leftX = x;
  const uint8_t leftWidth = division;

  const uint8_t rightX = (x + division + 1);
  const uint8_t rightWidth = (width - division - 1);

  generateHorizontalStep(leftX, y, leftWidth, height, depth - 1);
  generateHorizontalStep(rightX, y, rightWidth, height, depth - 1);
}

/*void print()
{
  for(size_t y = 0; y < 32; ++y)
  {
    for(size_t x = 0; x < 32; ++x)
      cout << tileMap[y][x];

    cout << endl;
  }
}
*/

/*int main()
{
  generateSubdivide(6);
  //print();

  cin.get();
}
*/





/*
inline bool isWalkable(TileType tile)
{
  switch (tile)
  {
    // Add cases for every
    // kind of 'walkable' tile
    case TileType::blankTile:
    case TileType::TileType::roadTileTile:
      return true;

    // Assume anything that isn't in
    // the above case list is not walkable
    default:
      return false;
  }
}
*/

/*
uint8_t determineTileType::roadTileType(uint8_t x, uint8_t y)
{
  uint8_t TileType::roadTileType = 0;

  if (((x + 1) < mapWidth) && isWalkable(tileMap[y][x + 1]))
    TileType::roadTileType |= (1 << 0);

  if ((x > 0) && isWalkable(tileMap[y][x - 1]))
    TileType::roadTileType |= (1 << 1);

  if (((y + 1) < mapHeight) && isWalkable(tileMap[y + 1][x]))
    TileType::roadTileType |= (1 << 2);

  if ((y > 0) && isWalkable(tileMap[y - 1][x]))
    TileType::roadTileType |= (1 << 3);

  return TileType::roadTileType;
}
*/

/*if isWalkable(tileMap[y][x])
  {
  TileType tileType = determineTileType::roadTileType(y,x);
  else TileType tileType = tileMap[y][x];
  }
*/

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
  //blankTile0,
  //blankTile1,
  roadTiles,
};

constexpr uint8_t const * tileMasks[]
{
  building0_mask,
  building1_mask,
  building2_mask,
  building3_mask,
  //blank tile mask?
  //TileType::roadTile tile masks?

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
