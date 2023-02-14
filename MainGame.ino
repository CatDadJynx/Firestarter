#include "MainGame.h"

Vector buildingLoc;

//bool isPaused = false;
bool isMinimapVisible = false;

void setup() {
  arduboy.begin();
  arduboy.clear();
  arduboy.initRandomSeed();
  generateSubdivide(15, 3);
}

uint8_t frame = 0;

void loop() {
  if (!arduboy.nextFrame()) {
    return;
  }
  arduboy.clear();
  
  //Game code here
  arduboy.pollButtons();
  // Handle input
  handleInput();
  
  if (isMinimapVisible == true)
  {
    drawMiniMap();
  }

  else
  {
    drawIsoMap();
  }
   
  debug();
  arduboy.display();
}

void handleInput()
{
   // Move cursor and camera
  if (arduboy.pressed(UP_BUTTON))
  {
      --camera.y;
      
      //update player
  }

  if (arduboy.pressed(DOWN_BUTTON))
  {
      ++camera.y;

      //update player
  }

  if (arduboy.pressed(LEFT_BUTTON))
  {
      --camera.x;
      
      //update player
  }

  if (arduboy.pressed(RIGHT_BUTTON))
  {
      ++camera.x;

      //update player
  }

  if(arduboy.justPressed(B_BUTTON))
  {
    isMinimapVisible = !isMinimapVisible;
  }
}


void debug()
{
  arduboy.print(camera.x);
  arduboy.print(camera.y);
}