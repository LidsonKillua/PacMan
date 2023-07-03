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

// Função que retorna a posição que será obtida com uma unidade de movimento na direção desejada, a partir de pos.
Position Entity::getMovement(Direction d, Position pos, char mapa[ROWS][COLS])
{
  /*
  Para cada direção, caso a tentativa de movimento fosse levar para fora do mapa, realiza o transporte para o outro extremo (portal). Caso contrário, apenas anda uma unidade na direção correspondente.
  */
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