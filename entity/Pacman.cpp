#include "pacman.hpp"

Pacman::Pacman()
{
}

Pacman::~Pacman()
{
}

bool Pacman::initialize()
{
  dir = Idle;
  intent = Idle;
  pos.x = 12;
  pos.y = 8;
  drawPos.x = pos.x * SIZE;
  drawPos.y = pos.y * SIZE;
  frameAtual = 0;
  tempAcumul = 0.0f;

  if (!textures[Right].loadFromFile(c_ImgCarDir)) // ler imagem direita
  {
    throw new ErroLeitura(c_ImgCarDir);
    return false;
  }
  sprite.setTexture(textures[Right]);
  sprite.setScale(sf::Vector2f(1.1f, 1.1f));

  if (!textures[Left].loadFromFile(c_ImgCarEsq)) // ler imagem esquerda
  {
    throw new ErroLeitura(c_ImgCarEsq);
    return false;
  }

  if (!textures[Down].loadFromFile(c_ImgCarDwn)) // ler imagem esquerda
  {
    throw new ErroLeitura(c_ImgCarDwn);
    return false;
  }

  if (!textures[Up].loadFromFile(c_ImgCarUp)) // ler imagem esquerda
  {
    throw new ErroLeitura(c_ImgCarUp);
    return false;
  }
  return true;
}

// Função pra mover o pacman
void Pacman::move(char mapa[ROWS][COLS])
{
  Position movement;

  // Caso seja possível se mover na direção da intenção do usuário, ela se torna a direção de movimento.
  int diffX = abs(drawPos.x - pos.x * SIZE);
  int diffY = abs(drawPos.y - pos.y * SIZE);
  if (canMove(intent, pos, mapa) && diffX <= TOLERANCE && diffY <= TOLERANCE && !isIdle)
    dir = intent;
  isIdle = false;

  // Se puder se mover na direção, realiza o movimento
  if (canMove(dir, pos, mapa))
  {
    updateAnimation();
    movement = getMovement(dir, pos, mapa);
    pos = movement;
    drawPos.x = pos.x * SIZE;
    drawPos.y = pos.y * SIZE;
  }
  /************* Preparação para o próximo movimento **************************
  Se, após o movimento, é possível se mover na direção da intent, já atualiza a direção
  ****************************************************************************/
  if (canMove(intent, pos, mapa))
    dir = intent;
  if (dir != Idle)
    sprite.setTexture(textures[dir]);
}

void Pacman::updateDrawPos(char mapa[ROWS][COLS])
{
  if (intent != dir && !canMove(dir, pos, mapa))
  {
    isIdle = true;
    // sprite.setTexture(textures[intent]);
  }
  Entity::updateDrawPos(mapa);
}

void Pacman::updateAnimation() // animacao
{
  // Acumula o tempo decorrido
  tempAcumul += defTempo;

  // Atualiza a animacao se o tempo acumulado for maior ou igual a taxa de atualizacao
  if (tempAcumul >= frameRate)
  {
    // Passa para o proximo frame
    frameAtual = (frameAtual + 1) % totalFrames;

    // Redefine o tempo acumulado
    tempAcumul = 0.0f;
  }
}

void Pacman::draw(sf::RenderWindow *window)
{
  int frameWidth = textures[Right].getSize().x / totalFrames;
  int frameHeight = textures[Right].getSize().y;
  sf::IntRect frameRect(frameAtual * frameWidth, 0, frameWidth, frameHeight);
  sprite.setTextureRect(frameRect);
  sprite.setPosition(drawPos.x, drawPos.y);
  window->draw(sprite);
}
