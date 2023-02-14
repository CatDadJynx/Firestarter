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

void generateHorizontalStep(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t depth, uint8_t maxOffset);
void generateVerticalStep(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t depth, uint8_t maxOffset);

/*
void generateHorizontalStep(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t depth);
void generateVerticalStep(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t depth);
*/

void generateSubdivide(uint8_t depth, uint8_t maxOffset)
{
  fill();
  generateVerticalStep(0, 0, 32, 32, depth, maxOffset);
}

/*
void generateSubdivide(uint8_t depth)
{
  fill();
  generateVerticalStep(0, 0, 32, 32, depth);
}
*/

void generateHorizontalStep(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t depth, uint8_t maxOffset)
{
  if(depth == 0)
    return;
    
  if(width < 2)
    return;
    
  if(height < 3)
    return;
    
  //Generate random number between -N and N
  uint8_t randomNumber = random(-maxOffset, maxOffset+1);
  
  //Calculate the position of the line
  const uint8_t division = randomNumber + (height/2);
  
  //Check to make sure the line is within the boundaries of the map
  if(division < 0 || division > height-2)
    return;
  
  fillHorizontalLine(x, y + division, width, TileType::roadTile);

  const uint8_t upperY = y;
  const uint8_t upperHeight = division;

  const uint8_t lowerY = (y + division + 1);
  const uint8_t lowerHeight = (height - division - 1);

  generateVerticalStep(x, upperY, width, upperHeight, depth - 1, maxOffset);
  generateVerticalStep(x, lowerY, width, lowerHeight, depth - 1, maxOffset);
}

void generateVerticalStep(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t depth, uint8_t maxOffset)
{
  if(depth == 0)
    return;
    
  if(height < 2)
    return;
    
  if(width < 3)
    return;
    
  //Generate random number between -N and N
  uint8_t randomNumber = random(-maxOffset, maxOffset+1);
  
  //Calculate the position of the line
  const uint8_t division = randomNumber + (width/2);
  
  //Check to make sure the line is within the boundaries of the map
  if(division < 0 || division > width-2)
    return;
  
  fillVerticalLine(x + division, y, height, TileType::roadTile);

  const uint8_t leftX = x;
  const uint8_t leftWidth = division;

  const uint8_t rightX = (x + division + 1);
  const uint8_t rightWidth = (width - division - 1);

  generateHorizontalStep(leftX, y, leftWidth, height, depth - 1, maxOffset);
  generateHorizontalStep(rightX, y, rightWidth, height, depth - 1, maxOffset);
}

/*
void generateHorizontalStep(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t depth)
{
  if(depth == 0)
    return;
  if(width < 2)
    return;
  if(height < 3)
    return;
  
  // Calculate the center of the area
  const uint8_t center = y + ((height - 2) / 2);
  // Calculate a random offset between -n and +n
  uint8_t N = 3;
  const uint8_t offset = random(N * 2) - N;
  // Calculate final position of the road/partition line
  const uint8_t division = center + offset;
  fillHorizontalLine(x, y + division, width, TileType::roadTile);
  const uint8_t upperY = y;
  const uint8_t upperHeight = division;
  const uint8_t lowerY = (y + division + 1);
  const uint8_t lowerHeight = (height - division - 1);
  generateVerticalStep(x, upperY, width, upperHeight, depth - 1);
  generateVerticalStep(x, lowerY, width, lowerHeight, depth - 1);
}
// Modified function
void generateVerticalStep(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t depth)
{
  if(depth == 0)
    return;
  if(height < 2)
    return;
  if(width < 3)
    return;
  // Calculate the center of the area
  const uint8_t center = x + ((width - 2) / 2);
  // Calculate a random offset between -n and +n
  uint8_t N = 3;
  const uint8_t offset = random(N * 2) - N;
  // Calculate final position of the road/partition line
  const uint8_t division = center + offset;
  fillVerticalLine(x + division, y, height, TileType::roadTile);
  const uint8_t leftX = x;
  const uint8_t leftWidth = division;
  const uint8_t rightX = (x + division + 1);
  const uint8_t rightWidth = (width - division - 1);
  generateHorizontalStep(leftX, y, leftWidth, height, depth - 1);
  generateHorizontalStep(rightX, y, rightWidth, height, depth - 1);
}
*/

/*
void generateHorizontalStep(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t depth, uint8_t N)
{
  if(depth == 0)
    return;
  if(width < 2)
    return;
  if(height < 3)
    return;
  
  //Calculate the centre of the current area
  const uint8_t centre_x = x + (width - 2) / 2;
  const uint8_t centre_y = y + (height - 2) / 2;
  
  //Calculate the offset of the partition, using the centre as the reference point
  const int8_t offset = rand() % (N * 2) - N;
  
  //Apply the offset to the centre
  uint8_t division = centre_y + offset;
  
  //If the offset is negative and the division is less than 0, set the division to 0 to prevent out of bounds errors
  if (offset < 0 && division < 0) {
    division = 0;
  }
  
  //If the offset is positive and the division is greater than the height, set the division to the height - 1 to prevent out of bounds errors
  if (offset > 0 && division > height) {
    division = height - 1;
  }
  
  fillHorizontalLine(x, y + division, width, TileType::roadTile);
  const uint8_t upperY = y;
  const uint8_t upperHeight = division;
  const uint8_t lowerY = (y + division + 1);
  const uint8_t lowerHeight = (height - division - 1);
  generateVerticalStep(x, upperY, width, upperHeight, depth - 1, N);
  generateVerticalStep(x, lowerY, width, lowerHeight, depth - 1, N);
}
void generateVerticalStep(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t depth, uint8_t N)
{
  if(depth == 0)
    return;
  if(height < 2)
    return;
  if(width < 3)
    return;
  
  //Calculate the centre of the current area
  const uint8_t centre_x = x + (width - 2) / 2;
  const uint8_t centre_y = y + (height - 2) / 2;
  
  //Calculate the offset of the partition, using the centre as the reference point
  int8_t offset = rand() % (N * 2) - N;
  
  //Apply the offset to the centre
  uint8_t division = centre_x + offset;
  
  //If the offset is negative and the division is less than 0, set the division to 0 to prevent out of bounds errors
  if (offset < 0 && division < 0) {
    division = 0;
  }
  
  //If the offset is positive and the division is greater than the width, set the division to the width - 1 to prevent out of bounds errors
  if (offset > 0 && division > width) {
    division = width - 1;
  }
  
  fillVerticalLine(x + division, y, height, TileType::roadTile);
  const uint8_t leftX = x;
  const uint8_t leftWidth = division;
  const uint8_t rightX = (x + division + 1);
  const uint8_t rightWidth = (width - division - 1);
  generateHorizontalStep(leftX, y, leftWidth, height, depth - 1, N);
  generateHorizontalStep(rightX, y, rightWidth, height, depth - 1, N);
}
*/

/*
void generateHorizontalStep(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t depth, uint8_t n)
{
  if(depth == 0)
    return;
  if(width < 2)
    return;
  if(height < 3)
    return;
  // Calculate the centre of the area
  const uint8_t centerY = y + ((height - 2) / 2);
  const uint8_t centerX = x + ((width - 2) / 2);
  // Calculate a random offset between -n and +n
  const uint8_t randOffset = random(n * 2) - n;
  // Add them together
  const uint8_t division = centerY + randOffset;
  fillHorizontalLine(x, division, width, TileType::roadTile);
  const uint8_t upperY = y;
  const uint8_t upperHeight = division;
  const uint8_t lowerY = (division + 1);
  const uint8_t lowerHeight = (height - division - 1);
  generateVerticalStep(x, upperY, width, upperHeight, depth - 1, n);
  generateVerticalStep(x, lowerY, width, lowerHeight, depth - 1, n);
}
void generateVerticalStep(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t depth, uint8_t n)
{
  if(depth == 0)
    return;
  if(height < 2)
    return;
  if(width < 3)
    return;
  // Calculate the centre of the area
  const uint8_t centerY = y + ((height - 2) / 2);
  const uint8_t centerX = x + ((width - 2) / 2);
  // Calculate a random offset between -n and +n
  const uint8_t randOffset = random(n * 2) - n;
  // Add them together
  const uint8_t division = centerX + randOffset;
  fillVerticalLine(division, y, height, TileType::roadTile);
  const uint8_t leftX = x;
  const uint8_t leftWidth = division;
  const uint8_t rightX = (division + 1);
  const uint8_t rightWidth = (width - division - 1);
  generateHorizontalStep(leftX, y, leftWidth, height, depth - 1, n);
  generateHorizontalStep(rightX, y, rightWidth, height, depth - 1, n);
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