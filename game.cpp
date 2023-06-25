#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

// Direção do Pacman ou Fantasmas
enum Direction
{
  Left,
  Right,
  Up,
  Down,
  Idle
};

// Struct do Pacman
typedef struct
{
  Direction intent;
  Direction dir;
  int posx;
  int posy;
} Pacman;

const int SIZE = 50; // Tamanho de cada célula do mapa

char mapa[11][21] = { // Mapa do jogo
    "11111111111111111111",
    "10000100222220100001",
    "10110101111110101101",
    "10100222222222200101",
    "10101101100110110101",
    "10000001000010000001",
    "10101101111110110101",
    "10100000000000000101",
    "10110101111110101101",
    "10000100022200100001",
    "11111111111111111111"};

Pacman pacman = {
  intent : Idle,
  dir : Idle,
  posx : 9,
  posy : 7
};

int pontos = 0;

bool canMove(Direction dir, int posy, int posx)
{
  if (dir == Up)
  {
    if (mapa[posy - 1][posx] != '1')
      return true;
  }
  else if (dir == Down)
  {
    if (mapa[posy + 1][posx] != '1')
      return true;
  }
  else if (dir == Left)
  {
    if (mapa[posy][posx - 1] != '1')
      return true;
  }
  else if (dir == Right)
  {
    if (mapa[posy][posx + 1] != '1')
      return true;
  }
  return false;
}

int main()
{
  // cria a janela
  sf::RenderWindow window(sf::VideoMode(1000, 550), "Pac-Man");

  // shape da parede
  sf::RectangleShape rectangle(sf::Vector2f(SIZE, SIZE));
  rectangle.setFillColor(sf::Color(0, 255, 255));
  rectangle.setOutlineThickness(-5);
  rectangle.setOutlineColor(sf::Color(50, 50, 50));

  // shape das pilulas
  sf::CircleShape pilula(5);
  pilula.setFillColor(sf::Color(255, 255, 0));
  pilula.setOutlineThickness(-1);
  pilula.setOutlineColor(sf::Color(255, 255, 255));

  // sprite do PacMan
  sf::Texture texture;
  if (!texture.loadFromFile("img/pacman.png"))
  {
    std::cout << "Erro lendo imagem pacman.png\n";
    return 0;
  }
  sf::Sprite sprite;
  sprite.setTexture(texture);

  // cria um relogio para medir o tempo do PacMan
  sf::Clock clock;

  // executa o programa enquanto a janela está aberta
  while (window.isOpen())
  {

    // verifica todos os eventos que foram acionados na janela desde a última iteração do loop
    sf::Event event;
    while (window.pollEvent(event))
    {
      // evento "fechar" acionado: fecha a janela
      if (event.type == sf::Event::Closed)
        window.close();

      // tecla pressionada
      if (event.type == sf::Event::KeyPressed)
      {
        if (event.key.code == sf::Keyboard::Left)
        {
          pacman.intent = Left;
        }
        else if (event.key.code == sf::Keyboard::Right)
        {
          pacman.intent = Right;
        }
        else if (event.key.code == sf::Keyboard::Up)
        {
          pacman.intent = Up;
        }
        else if (event.key.code == sf::Keyboard::Down)
        {
          pacman.intent = Down;
        }
      }
    }

    // Muda a posição do PacMan a cada 0.2 segundos
    if (clock.getElapsedTime() > sf::seconds(0.2))
    { // tempo desde último restart > 0.2s?
      if (canMove(pacman.intent, pacman.posy, pacman.posx))
        pacman.dir = pacman.intent;
      if (canMove(pacman.dir, pacman.posy, pacman.posx))
      {
        if (pacman.dir == Left)
          pacman.posx--;
        else if (pacman.dir == Right)
          pacman.posx++;
        else if (pacman.dir == Up)
          pacman.posy--;
        else if (pacman.dir == Down)
          pacman.posy++;
      }
      if (mapa[pacman.posy][pacman.posx] == '2')
      {
        mapa[pacman.posy][pacman.posx] = '0';
        pontos++;
        cout << "PONTOS: " << pontos << endl;
      }
      clock.restart(); // recomeça contagem do tempo
    }

    // limpa a janela com a cor preta
    window.clear(sf::Color::Black);

    // desenhar tudo aqui...

    // desenha paredes
    for (int i = 0; i < 11; i++)
      for (int j = 0; j < 21; j++)
      {
        if (mapa[i][j] == '1')
        {
          rectangle.setPosition(j * SIZE, i * SIZE);
          window.draw(rectangle);
        }
        else if (mapa[i][j] == '2')
        {
          pilula.setPosition(j * SIZE + SIZE / 2, i * SIZE + SIZE / 2);
          window.draw(pilula);
        }
      }

    // desenha PacMan
    sprite.setPosition(pacman.posx * SIZE, pacman.posy * SIZE);
    window.draw(sprite);

    // termina e desenha o frame corrente
    window.display();
  }
  return 0;
}
