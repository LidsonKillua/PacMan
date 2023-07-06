#include "game.hpp"
#include "../menu/menu.hpp"

Game::Game()
{
}

void Game::initialize(){
  // cria a janela
  if(!Reiniciando)
    window = new sf::RenderWindow(sf::VideoMode(TAMX, TAMY), "Pac-Man");

  initializeBackground();
  initializePilulas();

  // Inicializa o Pacman
  if (!pacman.initialize())
    throw new GameError("Erro ao inicializar Pacman!");

  // Inicializa os Fantasmas
  if (!Fantasma::initializeFantasmas(fantasmas))
    throw new GameError("Erro ao inicializar Fantasmas!");

  pontos = 0;
  Reiniciando = false;
}

void Game::initializeBackground()
{
  fd = new sf::Texture();
  // background
  if (!fd->loadFromFile("img/map.png"))
  {
    throw new GameError("Fatal Error");
  }
  background = new sf::Sprite(*fd);
}

void Game::initializePilulas()
{
  // shape das pilulas
  pilula = new sf::CircleShape(5);
  pilula->setFillColor(sf::Color(255, 255, 0));
  pilula->setOutlineThickness(-1);
  pilula->setOutlineColor(sf::Color(255, 255, 255));
}

void Game::gameLoop()
{
  // executa o programa enquanto a janela esta aberta
  while(!Reiniciando/*window->isOpen()*/)
  {
    eventLoop();
    updateGame();
    drawGame();
  }
}

void Game::eventLoop()
{

  // verifica todos os eventos que foram acionados na janela desde a ultima iteracao do loop
  sf::Event event;
  while (window->pollEvent(event))
  {
    // evento "fechar" acionado: fecha a janela
    if (event.type == sf::Event::Closed)
      window->close();

    // tecla pressionada
    else if (event.type == sf::Event::KeyPressed)
    {
      if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::P)
      {
        Menu * menu = new Menu(window);
        menu->run_menu();
        delete menu;

        if(menu->Reiniciar){
            Reiniciando = true;
            break;
        }
      }
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
}

void Game::updateGame()
{
  // Muda a posicao do PacMan a cada 0.2 segundos
  if (clock.getElapsedTime() > sf::seconds(0.2))
  {
    // tempo desde ultimo restart > 0.2s?

    // MOVE FANTASMAS
    for (int i = 0; i < numFantasmas; i++)
    {
      fantasmas[i].move(mapa, pacman, fantasmas);
    }

    // MOVE PACMAN
    pacman.move(mapa);

    if (mapa[pacman.pos.y][pacman.pos.x] == '2')
    {
      mapa[pacman.pos.y][pacman.pos.x] = '0';
      pontos++;
      cout << "PONTOS: " << pontos << endl;

      if (pontos == qtdPilulas)
        cout << "Voce Venceu!" << endl;
    }

    clock.restart(); // recomeca contagem do tempo
  }
}

// desenhar tudo aqui...
void Game::drawGame()
{
  // limpa a janela com a cor preta
  window->clear(sf::Color::Black);

  window->draw(*background); // desenha o mapa no fundo da tela

  for (int i = 0; i < ROWS; i++)
    for (int j = 0; j < COLS; j++)
    {
      if (mapa[i][j] == '2')
      {
        pilula->setPosition(j * SIZE + SIZE / 2, i * SIZE + SIZE / 2);
        window->draw(*pilula);
      }
    }

  // desenha PacMan
  pacman.draw(window);

  // desenha Fantasmas
  for (int i = 0; i < numFantasmas; i++)
    fantasmas[i].draw(window);

  // termina e desenha o frame corrente
  window->display();
}

Game::~Game()
{
  delete window;
  delete pilula;
  delete fd;
  delete background;
}
