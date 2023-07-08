#include "entity.hpp"

// Função que verifica se é possível se mover na direção desejada, a partir da posição pos
bool Entity::canMove(Direction d, Position pos, char mapa[ROWS][COLS])
{
  if (d == Up)
  {
    if (pos.y == 0) // É permitido mover para "fora do mapa" através do portal, que irá levar para a outra extremidade
    {
      return true;
    }
    if (isValidPos(pos.x, pos.y - 1, mapa)) // Caso não haja portal, verifica se a célula para a qual se deseja mover é válida.
    {
      return true;
    }
  }
  else if (d == Down)
  {
    if (pos.y == ROWS - 1)
      return true;
    if (isValidPos(pos.x, pos.y + 1, mapa))
      return true;
  }
  else if (d == Left)
  {
    if (pos.x == 0)
      return true;
    if (isValidPos(pos.x - 1, pos.y, mapa))
      return true;
  }
  else if (d == Right)
  {
    if (pos.x == COLS - 2)
      return true;
    if (isValidPos(pos.x + 1, pos.y, mapa))
      return true;
  }
  return false;
}

// Verifica se a posição x, y é válida. Implementação padrão: se a célula não é uma parede ('1')
bool Entity::isValidPos(int x, int y, char mapa[ROWS][COLS])
{
  return mapa[y][x] != '1';
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

void Entity::updateDrawPos(char mapa[ROWS][COLS])
{
  if (!canMove(dir, pos, mapa))
    return;
  if (dir == Left)
    drawPos.x -= SIZE / SMOOTHNESS;
  else if (dir == Right)
    drawPos.x += SIZE / SMOOTHNESS;
  if (dir == Up)
    drawPos.y -= SIZE / SMOOTHNESS;
  else if (dir == Down)
    drawPos.y += SIZE / SMOOTHNESS;
}

void Entity::setDrawPosFromPos()
{
  drawPos.x = pos.x * SIZE;
  drawPos.y = pos.y * SIZE;
}