#pragma once
#include "entity.hpp"
#include "pacman.hpp"
#include <queue>
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
  TipoFantasma tipo;
  sf::Texture texture;
  using Entity::Entity;
  void move(char mapa[ROWS][COLS], Pacman pacman);
  void draw(sf::RenderWindow *window);
  static bool initializeFantasmas(Fantasma fantasmas[]);

private:
  int posToNumber(Position pos);
  Position numberToPos(int number);
  Position getBestDirection(char mapa[ROWS][COLS], Position pos, Pacman pacman);
};