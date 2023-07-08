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
  Position drawPos;
  Position pos;

  bool canMove(Direction d, Position pos, char mapa[ROWS][COLS]);
  Position getMovement(Direction d, Position pos, char mapa[ROWS][COLS]);
  virtual bool isValidPos(int x, int y, char mapa[ROWS][COLS]);
  virtual void updateDrawPos(char mapa[ROWS][COLS]);
  void setDrawPosFromPos();
};