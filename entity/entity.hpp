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
  map<Direction, sf::Texture> textures;
  Direction dir;
  int posx;
  int posy;

  Entity();
  bool canMove(Direction dir, char mapa[ROWS][COLS]);
  bool canMove(Direction d, int posx, int posy, char mapa[ROWS][COLS]);
};