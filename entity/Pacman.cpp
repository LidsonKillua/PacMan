#include "pacman.hpp"

void Pacman::move(char mapa[ROWS][COLS])
{
  // tempo desde �ltimo restart > 0.2s?
  if (canMove(intent, mapa))
    dir = intent;
  if (canMove(dir, mapa))
  {
    if (dir == Left)
    {
      sprite.setTexture(textures[Left]);
      posx--;
    }
    else if (dir == Right)
    {
      sprite.setTexture(textures[Right]);
      posx++;
    }
    else if (dir == Up)
    {
      sprite.setTexture(textures[Up]);
      posy--;
    }
    else if (dir == Down)
    {
      sprite.setTexture(textures[Down]);
      posy++;
    }
  }
}