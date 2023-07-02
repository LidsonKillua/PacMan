#include "pacman.hpp"

// Função pra mover o pacman
void Pacman::move(char mapa[ROWS][COLS])
{
  Position movement;
  // Caso seja possível mover na direção que é a intenção do usuário, a intenção se torna a Direção de movimento.
  if (canMove(intent, pos, mapa))
    dir = intent;
  // Se puder se mover na direção, realiza o movimento
  if (canMove(dir, pos, mapa))
  {
    movement = getMovement(dir, pos, mapa);
    pos = movement;
    if (dir == Left)
      sprite.setTexture(textures[Left]);
    else if (dir == Right)
      sprite.setTexture(textures[Right]);
    else if (dir == Up)
      sprite.setTexture(textures[Up]);
    else if (dir == Down)
      sprite.setTexture(textures[Down]);
  }
}