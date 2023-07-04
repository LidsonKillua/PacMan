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

// Caminhos imagens Pac
const char c_ImgCarDir[17] = "img/carrodir.png";
const char c_ImgCarEsq[17] = "img/carroesq.png";
const char c_ImgCarDwn[17] = "img/carrodwn.png";
const char c_ImgCarUp[16] = "img/carroup.png";

//Caminhos imagens Policia
const char c_ImgPolDir[17] = /*"carro_policia.png"*/"img/ghost.png";


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

class ErroLeitura{
public:
    ErroLeitura(string msg);
};
