#pragma once

#include "entity.hpp"

// Definição da classe Pacman, herdando de Entity
class Pacman : public Entity
{
public:
  Direction intent;
  using Entity::Entity;
  void move(char mapa[ROWS][COLS]);
};