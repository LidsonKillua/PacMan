#pragma once

#include "entity.hpp"

// Definição da classe Pacman, herdando de Entity
class Pacman : public Entity
{
public:
  Direction intent;
  map<Direction, sf::Texture> textures;
  // Animation Variables
  const int totalFrames = 8;     // Numero total de frames na animacao
  const float frameRate = 0.01f; // Taxa de atualizacao da animacao
  const float defTempo = 1.0f;
  int frameAtual;
  float tempAcumul;
  using Entity::Entity;
  Pacman();
  ~Pacman();
  void move(char mapa[ROWS][COLS]);
  bool initialize();
  void updateAnimation();
  void draw(sf::RenderWindow *window);
};