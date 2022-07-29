constexpr uint8_t minimapTileSprites[] PROGMEM = 
{
  6, 6,
  //miniBuilding0
  0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,

  //miniBuilding1
  0x3f, 0x00, 0x3f, 0x00, 0x3f, 0x00,

  //miniBuilding2
  0x15, 0x2a, 0x15, 0x2a, 0x15, 0x2a,

  //miniBuilding3
  0x3f, 0x25, 0x29, 0x33, 0x25, 0x3f,

  //mini blank tile sprite
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

  //mini road sprites 0, 1, and 2?
};


constexpr uint8_t miniRoadSprites[] PROGMEM = 
{
  6, 6,
  //Intersection
  0x3f, 0x21, 0x35, 0x21, 0x25, 0x3f,

  //Up/Down
  0x3f, 0x21, 0x35, 0x21, 0x21, 0x3f,

  //Left/Right
  0x3f, 0x21, 0x25, 0x21, 0x25, 0x3f,

};


constexpr uint8_t blankTileWidth = 19;

constexpr uint8_t blankTileHeight = 9;

constexpr uint8_t blankTile[] PROGMEM =
{
  // Dimensions
  blankTileWidth, blankTileHeight,

  0x10, 0x10, 0x28, 0x28, 0x44, 0x44, 0x82, 0x82, 0x01, 0x01, 0x01, 0x82, 0x82, 0x44, 0x44, 0x28, 0x28, 0x10, 0x10,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

constexpr uint8_t building0Width = 19;
constexpr uint8_t building0Height = 19;

constexpr uint8_t building0[] PROGMEM
{
  // Dimensions
  building0Width, building0Height,

  // Frame 0 - building0
  0x00, 0xD0, 0x58, 0xBC, 0xBE, 0x7C, 0x7C, 0xFA, 0xFA, 0xF6, 0xF4, 0x6C, 0x28, 0x18, 0x10, 0x10, 0x00, 0x80, 0x00,
  0x00, 0x3E, 0x00, 0x7D, 0x00, 0xFB, 0x01, 0xF6, 0x02, 0xE9, 0x00, 0xF4, 0x00, 0xFA, 0x00, 0x7D, 0x00, 0x3E, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

constexpr uint8_t building0_mask[] PROGMEM
{
  // Frame 0 - building0
  0xF0, 0xF8, 0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFC, 0xFC, 0xF8, 0xF8, 0xF0, 0xF0, 0xE0,
  0x3F, 0x7F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0x3F,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
};

constexpr uint8_t building1Width = 19;
constexpr uint8_t building1Height = 28;

constexpr uint8_t building1[] PROGMEM
{
  // Dimensions
  building1Width, building1Height,

  // Frame 0 - building1
  0xe0, 0x50, 0x88, 0xd0, 0x70, 0xb0, 0x18, 0x0c, 0x8a, 0x51, 0x8a, 0x0c, 0x18, 0xb0, 0xf0, 0xd0, 0x88, 0x50, 0xe0,
  0xff, 0x00, 0x00, 0xff, 0xfd, 0x02, 0x79, 0xff, 0x02, 0x04, 0x02, 0xff, 0x41, 0x7d, 0x20, 0xff, 0x00, 0x00, 0xff,
  0x7f, 0x80, 0x00, 0xff, 0xba, 0x55, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x20, 0xbf, 0x10, 0xff, 0x00, 0x80, 0x7f,
  0x00, 0x00, 0x01, 0x01, 0x02, 0x03, 0x04, 0x07, 0x08, 0x08, 0x08, 0x07, 0x04, 0x03, 0x02, 0x01, 0x01, 0x00, 0x00,
};

constexpr uint8_t building1_mask[] PROGMEM
{
  // Frame 0 - building1
  0xF0, 0xF8, 0xFC, 0xF8, 0xF0, 0xF8, 0xF8, 0xFE, 0xFE, 0xFF, 0xFE, 0xFE, 0xF8, 0xF0, 0xF0, 0xF8, 0xFC, 0xF8, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x01, 0x07, 0x0F, 0x0F, 0x0F, 0x07, 0x01, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00,
};

constexpr uint8_t building2Width = 19;
constexpr uint8_t building2Height = 19;

constexpr uint8_t building2[] PROGMEM
{
  // Dimensions
  building2Width, building2Height,

  // Frame 0 - building2
  0x00, 0x80, 0x00, 0x10, 0x10, 0x18, 0x28, 0x6C, 0xF4, 0xF6, 0xFA, 0xFA, 0x7C, 0x7C, 0xBE, 0xBC, 0x58, 0xD0, 0x00,
  0x00, 0x3E, 0x00, 0x7D, 0x00, 0xFA, 0x00, 0xF4, 0x00, 0xE9, 0x02, 0xF6, 0x01, 0xFB, 0x00, 0x7D, 0x00, 0x3E, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

constexpr uint8_t building2_mask[] PROGMEM
{
  // Frame 0 - building2
  0xE0, 0xF0, 0xF0, 0xF8, 0xF8, 0xFC, 0xFC, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC, 0xF8, 0xF0,
  0x3F, 0x7F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0x3F,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
};

constexpr uint8_t building3Width = 19;
constexpr uint8_t building3Height = 25;

constexpr uint8_t building3[] PROGMEM
{
  // Dimensions
  building3Width, building3Height,

  // Frame 0 - building3
  0x00, 0x00, 0x80, 0x10, 0x20, 0x68, 0x70, 0xF4, 0xF8, 0xFA, 0xFC, 0xC8, 0x88, 0x70, 0x70, 0x20, 0x20, 0x80, 0x00,
  0x00, 0xD0, 0x85, 0xAE, 0x0B, 0x5C, 0x16, 0xB8, 0x2C, 0x71, 0x21, 0xBC, 0x90, 0x5E, 0x48, 0xAF, 0xA4, 0xD7, 0x00,
  0x00, 0x0D, 0x08, 0x1B, 0x01, 0x07, 0x22, 0x6E, 0x44, 0xDD, 0x45, 0x6E, 0x22, 0x37, 0x11, 0x1B, 0x08, 0x0D, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

constexpr uint8_t building3_mask[] PROGMEM
{
  // Frame 0 - building3
  0xF0, 0xF0, 0xF8, 0xF8, 0xFC, 0xFC, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFC, 0xFC, 0xF8, 0xF8, 0xF0, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0x0F, 0x1F, 0x1F, 0x3F, 0x3F, 0x7F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0x3F, 0x3F, 0x1F, 0x1F, 0x0F,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

constexpr uint8_t roadHeight = 9;
constexpr uint8_t roadWidth = 18;

constexpr uint8_t roadTiles[] PROGMEM =
{
  roadWidth, roadHeight,
  //Intersection
  0x10, 0x10, 0x28, 0x28, 0x44, 0x44, 0x82, 0xaa, 0x01, 0x11, 0x01, 0xaa, 0x82, 0x44, 0x44, 0x28, 0x28, 0x10, 0x10,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

  //Up/down
  0x10, 0x10, 0x28, 0x28, 0x44, 0x44, 0x82, 0xa2, 0x01, 0x11, 0x01, 0x8a, 0x82, 0x44, 0x44, 0x28, 0x28, 0x10, 0x10,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

  //Left/right
  0x10, 0x10, 0x28, 0x28, 0x44, 0x44, 0x82, 0x8a, 0x01, 0x11, 0x01, 0xa2, 0x82, 0x44, 0x44, 0x28, 0x28, 0x10, 0x10,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
