#pragma once

#include <SFML/Graphics.hpp>
#include "../globals/globals.hpp"
#include <iostream>
#include "../entity/pacman.hpp"
#include "../entity/fantasma.hpp"

class Game
{
public:
  sf::RenderWindow *window;
  sf::CircleShape *pilula;
  sf::Texture *fd;
  sf::Sprite *background;
  Pacman pacman;
  Fantasma fantasmas[numFantasmas];
  char mapa[ROWS][COLS] = {
      // Mapa do jogo
      "1111111111110111111111111",
      "1000000000000000000000001",
      "1011011111110111111101101",
      "1011011111110111111101101",
      "1000000000000000000000001",
      "1011111110111110111111101",
      "0002222222222222222222000",
      "1011101111110111111011101",
      "1000001000000000001000001",
      "1011101111110111111011101",
      "1000100222222222220010001",
      "1110111010111110101110111",
      "1000000010000000100000001",
      "1011111111110111111111101",
      "1000000000000000000000001",
      "1111111111110111111111111",
  };
  sf::Clock clock;
  int pontos;
  void initialize();
  void gameLoop();
  Game();
  ~Game();

private:
  void initializeBackground();
  void initializePilulas();
  void eventLoop();
  void updateGame();
  void drawGame();
};