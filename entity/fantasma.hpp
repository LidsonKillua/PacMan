#pragma once
#include "entity.hpp"
#include "pacman.hpp"
#include <queue>
#include <time.h>
using namespace std;

// Definição dos tipos de fantasma: aleatório ou perseguidor
enum TipoFantasma
{
  Aleatorio,
  Perseguidor
};

// Definição da classe Fantasma
class Fantasma : public Entity
{
public:
  bool isStart;
  Direction startDir;
  TipoFantasma tipo, oldtipo = Aleatorio;
  int distPacman;
  using Entity::Entity;
  void move(char mapa[ROWS][COLS], Pacman pacman, int index, Dificult dificuldade, int qtdJare);
  void draw(sf::RenderWindow *window);
  static vector<Fantasma> initializeFantasmas(Dificult dificuldade);
  void mudarCarroPolicia(int i);
  void updateAnimationf();
  // Animation Variables
  const int totalFrames = 8;     // Numero total de frames na animacao
  const float frameRate = 0.01f; // Taxa de atualizacao da animacao
  const float defTempo = 1.0f;
  int frameAtual;
  float tempAcumul;
  sf::Clock animation;

private:
  int posToNumber(Position pos);
  Position numberToPos(int number);
  Direction getMovePerseguidor(char mapa[ROWS][COLS], Position pos, Pacman pacman);
  Direction getMoveAleatorio(char mapa[ROWS][COLS], Position origin, Pacman pacman);
  bool EhEncruzilhadaVazia(char mapa[ROWS][COLS], Position pos);
};
