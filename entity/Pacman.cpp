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
  frameAtual = 0;
  tempAcumul = 0.0f;
  if (!textures[Right].loadFromFile("img/pac.png")) // ler imagem direita
  {
    std::cout << "Erro lendo imagem pac.png\n";
    return false;
  }
  sprite.setTexture(textures[Right]);
  sprite.setScale(sf::Vector2f(3.f, 3.f));

  if (!textures[Left].loadFromFile("img/pacesq.png")) // ler imagem esquerda
  {
    std::cout << "Erro lendo imagem pacesq.png\n";
    return false;
  }

  if (!textures[Down].loadFromFile("img/pacdown.png")) // ler imagem esquerda
  {
    std::cout << "Erro lendo imagem pacdown.png\n";
    return false;
  }

  if (!textures[Up].loadFromFile("img/pacup.png")) // ler imagem esquerda
  {
    std::cout << "Erro lendo imagem pacup.png\n";
    return false;
  }
  return true;
}

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
    updateAnimation();
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
  sprite.setPosition(pos.x * SIZE, pos.y * SIZE);
  window->draw(sprite);
}