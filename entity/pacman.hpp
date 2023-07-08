#pragma once

#include "entity.hpp"

// Definição da classe Pacman, herdando de Entity
class Pacman : public Entity
{
public:
  Direction intent;
  bool isIdle = false;
  // Animation Variables
  const int totalFrames = 8;     // Numero total de frames na animacao
  const float frameRate = 0.01f; // Taxa de atualizacao da animacao
  const float defTempo = 1.0f;
  int frameAtual;
  float tempAcumul;
  bool isValidPos(int x, int y, char mapa[ROWS][COLS]) override;
  void move(char mapa[ROWS][COLS]);
  void updateDrawPos(char mapa[ROWS][COLS]) override;
  bool initialize();
  void updateAnimation();
  void draw(sf::RenderWindow *window);
};
