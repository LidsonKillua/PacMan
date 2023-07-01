#include "entity.hpp"

Entity::Entity(){};

bool Entity::canMove(Direction d, char mapa[ROWS][COLS])
{
  if (d == Up)
  {
    if (mapa[posy - 1][posx] != '1')
      return true;
  }
  else if (d == Down)
  {
    if (mapa[posy + 1][posx] != '1')
      return true;
  }
  else if (d == Left)
  {
    if (mapa[posy][posx - 1] != '1')
      return true;
  }
  else if (d == Right)
  {
    if (mapa[posy][posx + 1] != '1')
      return true;
  }
  return false;
}

bool Entity::canMove(Direction d, int posx, int posy, char mapa[ROWS][COLS])
{
  if (d == Up)
  {
    if (mapa[posy - 1][posx] != '1')
      return true;
  }
  else if (d == Down)
  {
    if (mapa[posy + 1][posx] != '1')
      return true;
  }
  else if (d == Left)
  {
    if (mapa[posy][posx - 1] != '1')
      return true;
  }
  else if (d == Right)
  {
    if (mapa[posy][posx + 1] != '1')
      return true;
  }
  return false;
}