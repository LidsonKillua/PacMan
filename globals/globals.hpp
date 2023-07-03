#pragma once

#include <string>
using namespace std;

#define ROWS 16
#define COLS 26
#define SIZE 48        // Tamanho de cada celula do mapa
#define numFantasmas 1 // Alterar a Quantidade de Fantasmas
#define qtdPilulas 30  // Alterar a Quantidade de Pilulas
const int TAMX = 1200; // Tamanho da Janela
const int TAMY = 768;  // Tamanho da Janela

enum Direction
{
  Left,
  Right,
  Up,
  Down,
  Idle
};

struct Position
{
  int x;
  int y;
};

bool operator==(const Position &lhs, const Position &rhs);

class GameError : exception
{
public:
  string msg;
  GameError(string msg);
};
