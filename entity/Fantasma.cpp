#include "fantasma.hpp"

void Fantasma::move(char mapa[ROWS][COLS], Pacman pacman)
{
  Direction dir;
  dir = getMinPathToPacman(mapa, posx, posy, pacman);
  if (dir == Left)
    posx--;
  else if (dir == Right)
    posx++;
  else if (dir == Up)
    posy--;
  else if (dir == Down)
    posy++;
}

int Fantasma::posToNumber(int posx, int posy)
{
  return posy * COLS + posx;
}

pair<int, int> Fantasma::numberToPos(int number)
{
  int posx = number % COLS;
  int posy = number / COLS;
  return {posx, posy};
}

Direction Fantasma::getMinPathToPacman(char mapa[ROWS][COLS], int posx, int posy, Pacman pacman)
{
  if (pacman.dir == Idle)
    return Idle;
  queue<int> q;
  pair<int, int> pos;
  int origin, u, parent[ROWS * COLS];
  bool visited[ROWS * COLS] = {false};
  origin = posToNumber(posx, posy);
  q.push(origin);

  while (!q.empty())
  {
    u = q.front();
    q.pop();
    visited[u] = true;
    pos = numberToPos(u);
    vector<int> movable;

    if (pos.first == pacman.posx && pos.second == pacman.posy)
    {
      break;
    }

    if (canMove(Left, pos.first, pos.second, mapa))
      movable.push_back(posToNumber(pos.first - 1, pos.second));
    if (canMove(Right, pos.first, pos.second, mapa))
      movable.push_back(posToNumber(pos.first + 1, pos.second));
    if (canMove(Up, pos.first, pos.second, mapa))
      movable.push_back(posToNumber(pos.first, pos.second - 1));
    if (canMove(Down, pos.first, pos.second, mapa))
      movable.push_back(posToNumber(pos.first, pos.second + 1));

    for (auto v : movable)
    {
      if (!visited[v])
      {
        visited[v] = true;
        parent[v] = u;
        q.push(v);
      }
    }
  }
  if (u == origin)
    return Idle;
  while (parent[u] != origin)
  {
    u = parent[u];
  }
  pos = numberToPos(u);
  if (pos.first == posx - 1)
    return Left;
  else if (pos.first == posx + 1)
    return Right;
  else if (pos.second == posy - 1)
    return Up;
  else
    return Down;
}