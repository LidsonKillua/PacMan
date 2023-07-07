#include "game.hpp"
#include "../menu/menu.hpp"
#include <iostream>

void Game::initialize()
{
  // cria a janela
  if (!Reiniciando)
    window = new sf::RenderWindow(sf::VideoMode(TAMX, TAMY), "Pac-Man");

  initializeBackground();
  InitializeScore();
  initializePilulas();
  initializeGameOverScreen();

  // Inicializa o Pacman
  if (!pacman.initialize())
    throw new GameError("Erro ao inicializar Pacman!");

  // Inicializa os Fantasmas
  if (!Fantasma::initializeFantasmas(fantasmas))
    throw new GameError("Erro ao inicializar Fantasmas!");

  pontos = 0;
  Reiniciando = false;
  GameOver = false;
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

void Game::InitializeScore()
{
  font = new sf::Font();
  font->loadFromFile("fonts/emulogic.ttf");

  score.setFont(*font);
  score.setString("SCORE 000");
  score.setCharacterSize(25);
  score.setPosition(sf::Vector2f(628, 10));
}

void Game::initializeGameOverScreen()
{
  gameOverT = new sf::Texture();
  // game over screen
  if (!gameOverT->loadFromFile("img/wasted.png"))
  {
    throw new GameError("Fatal Error");
  }
  gameOverS = new sf::Sprite(*gameOverT);
}

// Loop principal do jogo.
void Game::gameLoop()
{
  // executa o programa enquanto a janela esta aberta e não está reiniciando
  while (!Reiniciando && window->isOpen())
  {
    eventLoop();
    if (!GameOver)
    {
      updateGame();
      updatePos();
    }
    drawGame();
  }
}

// Loop de eventos (teclas pressionadas, por exemplo.)
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
        Menu *menu = new Menu(window);
        menu->run_menu();
        delete menu;

        if (menu->Reiniciar)
        {
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

// Verifica o Game Over em que fantasma e Pacman cruzam um pelo outro, sem parar na mesma posição (discreta) do mapa.
bool Game::checkCrossGameOver(Direction prevDir, Fantasma fantasma)
{
  if (fantasma.pos == pacman.pos)
  {
    if (prevDir == Right && pacman.dir == Left)
      return true;
    if (prevDir == Left && pacman.dir == Right)
      return true;
    if (prevDir == Down && pacman.dir == Up)
      return true;
    if (prevDir == Up && pacman.dir == Down)
      return true;
  }
  return false;
}

// Checa o Game Over padrão
bool Game::checkGameOver()
{
  for (int i = 0; i < numFantasmas; i++)
  {
    if (fantasmas[i].pos == pacman.pos)
    {
      return true;
    }
  }
  return false;
}

// Checa a captura de pílulas (e possível vitória)
void Game::processPilulas()
{
  if (mapa[pacman.pos.y][pacman.pos.x] == '2')
  {
    mapa[pacman.pos.y][pacman.pos.x] = '0';
    pontos++;

    string pts = (pontos > 99 ? to_string(pontos) : (pontos > 9 ? "0" + to_string(pontos) : "00" + to_string(pontos)));

    score.setString("SCORE " + pts);

    if (pontos == qtdPilulas)
      score.setString("Voce Venceu!");
  }
}

// Realiza o Game Over
void Game::gameOver()
{
  GameOver = true;
}

// Atualiza o estado do jogo
void Game::updateGame()
{
  Direction prevDir;
  // Muda o estado do jogo a cada UPDATE_GAME_T segundos
  if (clock.getElapsedTime() > sf::seconds(UPDATE_GAME_T))
  {
    // MOVE FANTASMAS
    for (int i = 0; i < numFantasmas; i++)
    {
      // Registra a direção do fantasma antes do movimento
      prevDir = fantasmas[i].dir;
      // Movimenta o fantasma
      fantasmas[i].move(mapa, pacman, fantasmas);
      // Verifica o crossGameOver
      if (checkCrossGameOver(prevDir, fantasmas[i]))
      {
        gameOver();
        return;
      }
    }

    // MOVE PACMAN
    pacman.move(mapa);

    if (checkGameOver())
    {
      gameOver();
      return;
    }

    processPilulas();

    clock.restart(); // recomeca contagem do tempo
    posClock.restart();
  }
}

// Atualiza a posição das entidades em um loop de tempo menor, a fim de aumentar a suavidade da movimentação
void Game::updatePos()
{
  // Muda o estado do desenho a cada fração de UPDATE_GAME_T, determinada pelo grau de SMOOTHNESS
  if (posClock.getElapsedTime() > sf::seconds(UPDATE_GAME_T / SMOOTHNESS))
  {
    // Atualiza posição dos fantasmas
    for (int i = 0; i < numFantasmas; i++)
    {
      fantasmas[i].updateDrawPos(mapa);
    }

    // Atualiza posição do Pacman
    pacman.updateDrawPos(mapa);

    posClock.restart();
  }
}

// Desenha tudo
void Game::drawGame()
{
  // limpa a janela com a cor preta
  window->clear(sf::Color::Black);

  window->draw(*background); // desenha o mapa no fundo da tela
  window->draw(score);

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

  if (GameOver)
  {
    window->draw(*gameOverS);
  }

  // termina e desenha o frame corrente
  window->display();
}

Game::~Game()
{
  delete window;
  delete font;
  delete pilula;
  delete fd;
  delete background;
}
