#include "entity.hpp"

// Definição da classe Entity
Entity::Entity(){};

// Função que verifica se é possível se mover na direção desejada, a partir da posição pos
bool Entity::canMove(Direction d, Position pos, char mapa[ROWS][COLS])
{
  /*
  Para cada direção, se a tentativa de movimento for para fora do mapa, é possível mover (pois há um portal naquela posição). Caso contrário, verifica se não há uma parede na direção desejada.
  */
  if (d == Up)
  {
    if (pos.y == 0)
    {
      return true;
    }
    if (mapa[pos.y - 1][pos.x] != '1')
    {
      return true;
    }
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
    if (pos.x == COLS - 2)
      return true;
    if (mapa[pos.y][pos.x + 1] != '1')
      return true;
  }
  return false;
}

// Função que retorna a posição que será obtida com uma unidade de movimento na direção desejada, a partir de pos.
Position Entity::getMovement(Direction d, Position pos, char mapa[ROWS][COLS])
{
  /*
  Para cada direção, caso a tentativa de movimento fosse levar para fora do mapa, realiza o transporte para o outro extremo (portal). Caso contrário, apenas anda uma unidade na direção correspondente.
  */
  Position newPos = pos;
  if (d == Up)
  {
    if (newPos.y == 0)
      newPos.y = ROWS - 1;
    else
      newPos.y--;
  }
  else if (d == Down)
  {
    if (newPos.y == ROWS - 1)
      newPos.y = 0;
    else
      newPos.y++;
  }
  else if (d == Left)
  {
    if (newPos.x == 0)
      newPos.x = COLS - 2;
    else
      newPos.x--;
  }
  else if (d == Right)
  {
    if (newPos.x == COLS - 2)
      newPos.x = 0;
    else
      newPos.x++;
  }
  return newPos;
}