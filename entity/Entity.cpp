#include "entity.hpp"

// Definição da classe Entity
Entity::Entity(){};

bool Entity::canMove(Direction d, Position pos, char mapa[ROWS][COLS])
{
  if (d == Up)
  {
    if (pos.y == 0)
      return true;
    if (mapa[pos.y - 1][pos.x] != '1')
      return true;
  }
  else if (d == Down)
  {
    if (pos.y == ROWS - 1)
      return true;
    if (mapa[pos.y + 1][pos.x] != '1')
      return true;
  }
  else if (d == Left)
  {
    if (pos.x == 0)
      return true;
    if (mapa[pos.y][pos.x - 1] != '1')
      return true;
  }
  else if (d == Right)
  {
    if (pos.x == COLS - 1)
      return true;
    if (mapa[pos.y][pos.x + 1] != '1')
      return true;
  }
  return false;
}

Position Entity::getMovement(Direction d, Position pos, char mapa[ROWS][COLS])
{
  if (d == Up)
  {
    if (pos.y == 0)
      pos.y = ROWS - 1;
    else
      pos.y--;
  }
  else if (d == Down)
  {
    if (pos.y == ROWS - 1)
      pos.y = 0;
    else
      pos.y++;
  }
  else if (d == Left)
  {
    if (pos.x == 0)
      pos.x = COLS - 1;
    else
      pos.x--;
  }
  else if (d == Right)
  {
    if (pos.x == COLS - 1)
      pos.x = 0;
    else
      pos.x++;
  }
  return pos;
}