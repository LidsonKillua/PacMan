#include "game.hpp"
#include "../menu/menu.hpp"
#include "../menu/fim.hpp"
#include "../menu/escDif.hpp"
#include <iostream>

void Game::initialize()
{
  // cria a janela
  if (!Reiniciando)
    window = new sf::RenderWindow(sf::VideoMode(TAMX, TAMY), "Pac-Man");

  EscolherDificuldade();

  initializeBackground();
  InitializeScore();
  initializePilulas();

  // Inicializa o Pacman
  if (!pacman.initialize())
    throw new GameError("Erro ao inicializar Pacman!");

  // Inicializa os Fantasmas
  fantasmas = Fantasma::initializeFantasmas(dificuldade);
  for (int i = 0; i < numFantasmas; i++)
  {
    fantasmas[i].mudarCarroPolicia(i);
  }

  initializeAllAudio();

  pontos = 0;
  Reiniciando = false;
  GameOver = false;
}

void Game::initializeAllAudio()
{
  if (!swatMusic.openFromFile(audio_swat))
    throw new ErroLeitura(audio_swat);
  swatMusic.setPlayingOffset(sf::seconds(2.f));

  if (!mscBichoVino.openFromFile(audio_BichoVindo))
    throw new ErroLeitura(audio_BichoVindo);
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

// Loop principal do jogo.
void Game::gameLoop()
{
  // executa o programa enquanto a janela esta aberta e não está reiniciando
  while (!Reiniciando && window->isOpen())
  {
    eventLoop();
    updateGame();
    updatePos();
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
        pauseAllAudio();
        Menu *menu = new Menu(window);
        menu->run_menu();
        delete menu;

        if (menu->Reiniciar)
        {
          Reiniciando = true;
          break;
        }
        else
          turnOnOffSwatMusic();
      }
      if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A)
      {
        pacman.intent = Left;
      }
      else if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D)
      {
        pacman.intent = Right;
      }
      else if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
      {
        pacman.intent = Up;
      }
      else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
      {
        pacman.intent = Down;
      }
    }
  }
}

// Verifica o Game Over em que fantasma e Pacman cruzam um pelo outro, sem parar na mesma posição (discreta) do mapa.
bool Game::checkCrossGameOver(Direction prevDir)
{
  for (auto fantasma : fantasmas)
  {
    if (fantasma.pos == pacman.pos)
    {
      if (prevDir == Right && fantasma.dir == Left)
        return true;
      if (prevDir == Left && fantasma.dir == Right)
        return true;
      if (prevDir == Down && fantasma.dir == Up)
        return true;
      if (prevDir == Up && fantasma.dir == Down)
        return true;
    }
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

void Game::turnOnOffSwatMusic()
{
  if (perseguir)
  {
    swatMusic.play();
    updateSwatMusic();
  }
  else
    swatMusic.pause();
}

void Game::updateSwatMusic()
{
  if (pacman.dir == Idle)
    swatMusic.setVolume(20);
  else if (fantasmas[0].distPacman > 0)
    swatMusic.setVolume(1.0 / fantasmas[0].distPacman * 100);
}

// Checa a captura de pílulas (e possível vitória)
void Game::processPilulas()
{
  if (mapa[pacman.pos.y][pacman.pos.x] == '2')
  {
    mapa[pacman.pos.y][pacman.pos.x] = '0';
    pontos++;
    cont++;

    if (dificuldade == Normal)
    {
      // Habilita/Desabilita o perseguidor a cada 20 pílulas
      if (cont >= 20)
      {
        perseguir = !perseguir;
        AltPerseguidor(perseguir);
        cont = 0;
        turnOnOffSwatMusic();
      }
    }
    else if (dificuldade == Hard)
    {
      // Habilita o perseguidor por 40 pílulas e desabilita por 20
      if ((perseguir && cont >= 40) || (!perseguir && cont >= 20))
      {
        perseguir = !perseguir;
        AltPerseguidor(perseguir);
        cont = 0;
        turnOnOffSwatMusic();
      }
    }

    string pts = (pontos > 99 ? to_string(pontos) : (pontos > 9 ? "0" + to_string(pontos) : "00" + to_string(pontos)));

    score.setString("SCORE " + pts);

    if (pontos == qtdPilulas)
    {
      score.setString("Voce Venceu!");

      pauseAllAudio();
      Final *menuF = new Final(window, false);
      menuF->run_menu();

      if (menuF->Reiniciar)
      {
        Reiniciando = true;
      }

      delete menuF;
    }
  }
}

// Realiza o Game Over
void Game::gameOver()
{
  pauseAllAudio();
  Final *menuF = new Final(window, true);
  menuF->run_menu();

  if (menuF->Reiniciar)
  {
    Reiniciando = true;
  }

  delete menuF;
}

void Game::pauseAllAudio()
{
  swatMusic.pause();
}

// Atualiza o estado do jogo
void Game::updateGame()
{
  Direction prevDir;
  Position prevPos;
  // Muda o estado do jogo a cada UPDATE_GAME_T segundos
  if (clock.getElapsedTime() > sf::seconds(UPDATE_GAME_T))
  {
    // Registra a direção e posição do fantasma antes do movimento
    prevDir = pacman.dir;
    prevPos = pacman.pos;

    // Se houver Swat (perseguidor)
    if (perseguir)
    {
      // Inicia a música da Swat caso Pacman esteja fazendo seu primeiro movimento
      if (pacman.dir == Idle && pacman.intent != Idle)
        turnOnOffSwatMusic();
      updateSwatMusic();
    }

    // MOVE PACMAN
    pacman.move(mapa);

    // Verifica o crossGameOver
    if (checkCrossGameOver(prevDir))
    {
      pacman.pos = prevPos;
      pacman.setDrawPosFromPos();
      gameOver();
      return;
    }

    // MOVE FANTASMAS
    for (int i = 0; i < numFantasmas; i++)
      fantasmas[i].move(mapa, pacman, i);

    // Verifica Game Over padrão
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

void Game::EscolherDificuldade()
{
  EscDif *esc = new EscDif(window);
  dificuldade = esc->run_escDif();
  delete esc;
}

void Game::AltPerseguidor(bool sim)
{
    if(sim){
        fantasmas[1].tipo = Perseguidor;
        mscBichoVino.stop();
        mscBichoVino.play();
        //mscBichoVino.
    }
    else
        fantasmas[1].tipo = Aleatorio;
}
