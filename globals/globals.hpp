#pragma once

#include <string>
using namespace std;

// Constantes do jogo
#define ROWS 16
#define COLS 26
#define SIZE 48             // Tamanho de cada celula do mapa
#define numFantasmas 4      // Alterar a Quantidade de Fantasmas
const int qtdPilulas = 177; // Alterar a Quantidade de Pilulas
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

// Caminhos imagens dos policiais (virados para direita)
const char c_ImgPolDir[4][25] = {
    "img/carro_policiadir.png",
    "img/carro_nypddir.png",
    "img/carro_ufvdir.png",
    "img/carro_apoiodir.png",
};

// Caminhos imagens dos policiais (virados para esquerda)
const char c_ImgPolEsq[4][25] = {
    "img/carro_policiaesq.png",
    "img/carro_nypdesq.png",
    "img/carro_ufvesq.png",
    "img/carro_apoioesq.png",
};

// Caminhos imagens dos policiais (virados para cima)
const char c_ImgPolUp[4][25] = {
    "img/carro_policiaup.png",
    "img/carro_nypdup.png",
    "img/carro_ufvup.png",
    "img/carro_apoioup.png",
};

// Caminhos imagens dos policiais (virados para baixo)
const char c_ImgPolDwn[4][25] = {
    "img/carro_policiadwn.png",
    "img/carro_nypddwn.png",
    "img/carro_ufvdwn.png",
    "img/carro_apoiodwn.png",
};

// Caminhos imagens Perseguidor(SWAT)
const char c_ImgSwtDir[25] = "img/carro_swatdir.png";
const char c_ImgSwtEsq[25] = "img/carro_swatesq.png";
const char c_ImgSwtUp[25] = "img/carro_swatup.png";
const char c_ImgSwtDwn[25] = "img/carro_swatdnw.png";

//Imagem inicial
const char c_ImgInicio[17] = "img/wasted.png";

const char c_ImgJare[17] = "img/jare.png";

/************* CAMINHOS PARA ARQUIVOS DE ÁUDIO ****************/
//Musica inicial
const char c_MscIni[25] = "audio/musicamenu.wav";
const char c_MscMenu[25] = "audio/musicamenu.wav";

const char audio_swat[25] = "audio/swat.wav";
const char audio_BichoVindo[33] = "audio/Ao-bicho-vindo-muleque.wav";
const char audio_motor[25] = "audio/Motorcar.wav";

// lista de áudios de Derrota
const int qtdMscD = 3;
const char audios_FinaisD[qtdMscD][50] = {
    "audio/Derrota/Musica/tema-triste-toguro.wav",
    "audio/Derrota/Musica/Naruto-Funk-Triste.wav",
    "audio/Derrota/Musica/titanic-parody.wav"
};

const int qtdFalasD = 4;
const char falas_FinaisD[qtdFalasD][50] = {
    "audio/Derrota/Fala/me-ferrei-amigos-estevao.wav",
    "audio/Derrota/Fala/o-moreno-ta-ingnorante.wav",
    "audio/Derrota/Fala/super-mario-death.wav",
    "audio/Derrota/Fala/the-price-is-right.wav"
};

// lista de áudios de Vitória
const int qtdMscV = 2;
const char audios_FinaisV[qtdMscV][50] = {
    "audio/Vitoria/Musica/giga-chad-theme.wav",
    "audio/Vitoria/Musica/baby-dont-hurt-me.wav"
};

const int qtdFalasV = 2;
const char falas_FinaisV[qtdFalasV][50] = {
    "audio/Vitoria/Fala/asmei.wav",
    "audio/Vitoria/Fala/cr_suuu.wav"
};

struct Position
{
  int x;
  int y;
};

// Posições iniciais
const Position PAC_POS = {12, 8};
const Position FAN1_POS = {7, 8};
const Position FAN2_POS = {8, 8};
const Position FAN3_POS = {16, 8};
const Position FAN4_POS = {17, 8};

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
