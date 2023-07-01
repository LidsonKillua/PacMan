#pragma once
#include "entity.hpp"
#include "pacman.hpp"
#include <queue>
using namespace std;

enum TipoFantasma
{
  Aleatorio,
  Perseguidor
};

class Fantasma : public Entity
{
public:
  TipoFantasma tipo;
  using Entity::Entity;
  void move(char mapa[ROWS][COLS], Pacman pacman);

private:
  int posToNumber(int posx, int posy);
  pair<int, int> numberToPos(int number);
  Direction getMinPathToPacman(char mapa[ROWS][COLS], int posx, int posy, Pacman pacman);
};