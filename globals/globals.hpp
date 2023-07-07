#pragma once

#include <string>
using namespace std;

// Variáveis do jogo
#define ROWS 16
#define COLS 26
#define SIZE 48             // Tamanho de cada celula do mapa
#define numFantasmas 2      // Alterar a Quantidade de Fantasmas
const int qtdPilulas = 17/*7*/; // Alterar a Quantidade de Pilulas
const int TAMX = 1200;      // Tamanho da Janela
const int TAMY = 768;       // Tamanho da Janela

// Variáveis de animação
#define UPDATE_GAME_T 0.2 // Tempo para atualizar o jogo (1 ciclo)
#define SMOOTHNESS 8      // Define quantas vezes a posição é atualizada em 1 ciclo
#define TOLERANCE 5       // Tolerância de quantos pixels o Pacman pode passar da posição de virar e, ao receber o intent, ainda ser capaz de se mover nessa direção

// Caminhos imagens Pac
const char c_ImgCarDir[17] = "img/carrodir.png";
const char c_ImgCarEsq[17] = "img/carroesq.png";
const char c_ImgCarDwn[17] = "img/carrodwn.png";
const char c_ImgCarUp[16] = "img/carroup.png";

// Caminhos imagens Policia
const char c_ImgPolDir[25] = "img/carro_policiadir.png";
const char c_ImgPolEsq[25] = "img/carro_policiaesq.png";
const char c_ImgPolUp[25] = "img/carro_policiaup.png";
const char c_ImgPolDwn[25] = "img/carro_policiadnw.png";

enum Direction
{
  Left,
  Right,
  Up,
  Down,
  Idle
};

enum Dificult
{
  Easy,
  Normal,
  Hard
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

class ErroLeitura
{
public:
  ErroLeitura(string msg);
};
