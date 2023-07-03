#pragma once

#include <SFML/Graphics.hpp>
#include "../globals/globals.hpp"
#include <iostream>
#include <map>
using namespace std;

class Entity
{
public:
  sf::Sprite sprite;
  Direction dir;
  Position pos;

  Entity();
  bool canMove(Direction d, Position pos, char mapa[ROWS][COLS]);
  Position getMovement(Direction d, Position pos, char mapa[ROWS][COLS]);
};