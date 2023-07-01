#pragma once

#include "entity.hpp"

class Pacman : public Entity
{
public:
  Direction intent;
  using Entity::Entity;
  void move(char mapa[ROWS][COLS]);
};