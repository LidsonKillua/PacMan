#include "globals.hpp"

bool operator==(const Position &a, const Position &b)
{
  return a.x == b.x && a.y == b.y;
}

GameError::GameError(string msg)
{
  this->msg = msg;
}

ErroLeitura::ErroLeitura(string caminho){
    GameError("Erro lendo imagem: " + caminho + "\n");
}
