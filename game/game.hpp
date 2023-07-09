#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../globals/globals.hpp"
#include <iostream>
#include <vector>
#include "../entity/pacman.hpp"
#include "../entity/fantasma.hpp"

class Game
{
public:
  sf::Music swatMusic;
  sf::RenderWindow *window;
  sf::CircleShape *pilula;
  sf::Texture *fd;
  sf::Sprite *background;

  sf::Font *font;
  sf::Text score;

  Dificult dificuldade;
  Pacman pacman;
  vector<Fantasma> fantasmas;
  char mapa[ROWS][COLS] = {
      // Mapa do jogo
      // 0: Rua
      // 1: Parede
      // 2: Pilulas
      // 3: Parede Invisivel/Onde so fantasma anda
      "1111111111110111111111111",
      "1222222222222222222222221",
      "1211211111112111111121121",
      "1211211111112111111121121",
      "1222222222222222222222221",
      "1211111112111112111111121",
      "0222222222222222222222220",
      "1211121111112111111211121",
      "1222221333300033331222221",
      "1211121111112111111211121",
      "1222122222222222222212221",
      "1112111212111112121112111",
      "1222222212222222122222221",
      "1211111111112111111111121",
      "1222222222222222222222221",
      "1111111111110111111111111",
  };
  sf::Clock clock;
  sf::Clock posClock;
  int pontos, cont = 0;
  bool Reiniciando = false;
  bool GameOver = false;
  bool perseguir = true;
  void initialize();
  void gameLoop();
  ~Game();

private:
  void initializeAllAudio();
  void initializeBackground();
  void initializePilulas();
  void InitializeScore();
  void EscolherDificuldade();
  void eventLoop();
  bool checkCrossGameOver(Direction prevDir);
  bool checkGameOver();
  void turnOnOffSwatMusic();
  void updateSwatMusic();
  void processPilulas();
  void gameOver();
  void pauseAllAudio();
  void updateGame();
  void updatePos();
  void drawGame();
};
