#include "fantasma.hpp"

vector<Fantasma> Fantasma::initializeFantasmas(Dificult dificuldade)
{
  vector<Fantasma> fantasmas(numFantasmas, Fantasma());
  for (int i = 0; i < numFantasmas; i++)
  {
    fantasmas[0].tipo = Aleatorio;
    fantasmas[i].dir = Idle;
    fantasmas[i].isStart = true;
    fantasmas[i].startDir = Right;
    if (!fantasmas[i].textures[Right].loadFromFile(c_ImgPolDir[i])) // ler imagem direita
      throw new ErroLeitura(c_ImgPolDir[i]);
    if (!fantasmas[i].textures[Left].loadFromFile(c_ImgPolEsq[i])) // ler imagem esq
      throw new ErroLeitura(c_ImgPolEsq[i]);
    if (!fantasmas[i].textures[Up].loadFromFile(c_ImgPolUp[i])) // ler imagem cima
      throw new ErroLeitura(c_ImgPolUp[i]);
    if (!fantasmas[i].textures[Down].loadFromFile(c_ImgPolDwn[i])) // ler imagem baixo
      throw new ErroLeitura(c_ImgPolDwn[i]);

    fantasmas[i].sprite.setTexture(fantasmas[i].textures[Right]);
    fantasmas[i].sprite.setScale(sf::Vector2f(1.1f, 1.1f));
  }

  if (dificuldade > Easy)
  {
    fantasmas[1].tipo = Perseguidor;
  }
  fantasmas[0].pos = FAN1_POS;
  fantasmas[0].setDrawPosFromPos();
  fantasmas[1].pos = FAN2_POS;
  fantasmas[1].setDrawPosFromPos();
  fantasmas[2].pos = FAN3_POS;
  fantasmas[2].setDrawPosFromPos();
  fantasmas[2].sprite.setTexture(fantasmas[2].textures[Left]);
  fantasmas[2].startDir = Left;
  fantasmas[3].pos = FAN4_POS;
  fantasmas[3].setDrawPosFromPos();
  fantasmas[3].sprite.setTexture(fantasmas[3].textures[Left]);
  fantasmas[3].startDir = Left;
  return fantasmas;
}

void Fantasma::updateAnimationf() // animacao
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

void Fantasma::mudarCarroPolicia(int i) // animacao
{
  if (tipo == Perseguidor)
  {
    if (!textures[Right].loadFromFile(c_ImgSwtDir)) // ler imagem direita
      throw new ErroLeitura(c_ImgSwtDir);
    if (!textures[Left].loadFromFile(c_ImgSwtEsq)) // ler imagem esq
      throw new ErroLeitura(c_ImgSwtEsq);
    if (!textures[Up].loadFromFile(c_ImgSwtUp)) // ler imagem cima
      throw new ErroLeitura(c_ImgSwtUp);
    if (!textures[Down].loadFromFile(c_ImgSwtDwn)) // ler imagem baixo
      throw new ErroLeitura(c_ImgSwtDwn);
  }
  else
  {
    if (!textures[Right].loadFromFile(c_ImgPolDir[i])) // ler imagem direita
      throw new ErroLeitura(c_ImgPolDir[i]);
    if (!textures[Left].loadFromFile(c_ImgPolEsq[i])) // ler imagem esq
      throw new ErroLeitura(c_ImgPolEsq[i]);
    if (!textures[Up].loadFromFile(c_ImgPolUp[i])) // ler imagem cima
      throw new ErroLeitura(c_ImgPolUp[i]);
    if (!textures[Down].loadFromFile(c_ImgPolDwn[i])) // ler imagem baixo
      throw new ErroLeitura(c_ImgPolDwn[i]);
  }
}

// Função pra mover o fantasma, herdando de Entity
void Fantasma::move(char mapa[ROWS][COLS], Pacman pacman, int index, Dificult dificuldade, int qtdJare)
{
  // Caso o Pacman esteja parado (início de jogo), nada ocorre
  if (pacman.dir == Idle)
    return;

  updateAnimationf();

  if (tipo != oldtipo)
  {
    mudarCarroPolicia(index);
  }
  oldtipo = tipo;

  // Move-se para a direção que já estava determinada
  pos = getMovement(dir, pos, mapa);
  setDrawPosFromPos();

  // Obtem a próxima direção para já se preparar para a ação
  if (tipo == Perseguidor)
    dir = getMovePerseguidor(mapa, pos, pacman);
  else
    dir = getMoveAleatorio(mapa, pos, pacman);

  // Muda o sprite
  if (dir != Idle)
    sprite.setTexture(textures[dir]);

  if(dificuldade == Hard && qtdJare < 3 && EhEncruzilhadaVazia(mapa, pos) && (rand() % 10 > 7)){ // 30%
        mapa[pos.x][pos.y] = '4';
        qtdJare++;
  }
}

bool Fantasma::EhEncruzilhadaVazia(char mapa[ROWS][COLS], Position pos){
  int qtdParedes = 0;

  if(mapa[pos.x][pos.y] == '0'){
    if(mapa[pos.x-1][pos.y-1] == '1')
        qtdParedes++;
    if(mapa[pos.x-1][pos.y+1] == '1')
        qtdParedes++;
    if(mapa[pos.x+1][pos.y-1] == '1')
        qtdParedes++;
    if(mapa[pos.x+1][pos.y+1] == '1')
        qtdParedes++;

    if(qtdParedes < 2 )
        return true;
  }

  return false;
}

/******************************************************************************
Função pra transformar posição da matriz em um número de vértice. O intuito disso
é poder ver a matriz como uma espécie de grafo. Nesse grafo, cada posição da matriz
corresponderia a um vértice, identificado por esse número. As arestas são calculadas
dinâmicamente, pela checagem dos nós adjacentes e verificação se é possível se mover
para essa posição (é possível caso não seja uma parede).
******************************************************************************/
int Fantasma::posToNumber(Position pos)
{
  return pos.y * COLS + pos.x;
}

// Função pra transformar número de vértice em uma posição da matriz
Position Fantasma::numberToPos(int number)
{
  Position pos = {number % COLS, number / COLS};
  return pos;
}

/******************************************************************************
Função que realiza uma BFS no mapa até encontrar o Pacman, descobrindo assim o
menor caminho. Ela retorna a direção que corresponde ao primeiro movimento que o
fantasma deve realizar
******************************************************************************/
Direction Fantasma::getMovePerseguidor(char mapa[ROWS][COLS], Position origin, Pacman pacman)
{
  // Variáveis para o BFS
  queue<int> q;
  Position pos;
  int originV, u;
  bool visited[ROWS * COLS] = {false};
  /*
  Esse array guarda quem é o vértice "pai" de cada vértice x dentro da BFS. Ou seja,
  o vértice a partir do qual se chegou no vértice x. Ele é necessário para reconstruir
  o menor caminho até o Pacman, no sentido contrário: do Pacman à posição original.
  Assim, é possível saber qual deve ser o primeiro movimento do Fantasma.
   */
  int parent[ROWS * COLS];
  // Converte a posição do fantasma em um número de vértice que a representa
  originV = posToNumber(origin);
  // Adiciona esse vértice na queue da BFS
  q.push(originV);

  // Enquanto houverem vértices na queue, executa a BFS
  while (!q.empty())
  {
    u = q.front();
    q.pop();
    // Marca vértice como visitado
    visited[u] = true;
    // Converte número do vértice para uma posição no mapa
    pos = numberToPos(u);
    // Vetor que armazena os vértices adjacentes
    vector<int> adjacents;

    // Ao encontrar o Pacman, encerra a busca
    if (pos == pacman.pos)
      break;

    /*
    Checa se Fantasma, a partir da posição atual, pode se mover para cada direção,
    e caso possa, adiciona o número do vértice correspondente a essa nova posição à lista de adjacentes.
    */

    if (canMove(Left, pos, mapa))
      adjacents.push_back(posToNumber(getMovement(Left, pos, mapa)));
    if (canMove(Right, pos, mapa))
      adjacents.push_back(posToNumber(getMovement(Right, pos, mapa)));
    if (canMove(Up, pos, mapa))
      adjacents.push_back(posToNumber(getMovement(Up, pos, mapa)));
    if (canMove(Down, pos, mapa))
      adjacents.push_back(posToNumber(getMovement(Down, pos, mapa)));

    // Percorre os nós adjacentes
    for (auto v : adjacents)
    {
      // Verifica se já não foi visitado
      if (!visited[v])
      {
        // Já marca como visitado, para evitar mais visitas desnecessárias
        visited[v] = true;
        /* Grava que o pai do nó adjacente "v" é "u", pois estamos acessando "v" a partir de "u"*/
        parent[v] = u;
        q.push(v);
      }
    }
  }
  // O último nó "u" visitado corresponde à posição do Pacman. Se o Pacman está na mesma posição que o fantasma, o fantasma deve apenas ficar parado
  if (u == originV)
    return Idle;
  // Reconstrói o caminho até o nó cujo pai é o nó de origem do Fantasma (pra rastrear o primeiro movimento do Fantasma)
  int distPacman = 1;
  while (parent[u] != originV)
  {
    u = parent[u];
    distPacman++;
  }
  this->distPacman = distPacman;
  // Traduz o número do vértice em posição no mapa, para saber pra qual posição o fantasma deve ir em seu primeiro movimento.
  pos = numberToPos(u);
  // Testa todas as direções para encontrar a direção que me fará chegar a "pos", que corresponde à direção do primeiro movimento.
  if (getMovement(Left, origin, mapa) == pos)
    return Left;
  else if (getMovement(Right, origin, mapa) == pos)
    return Right;
  else if (getMovement(Up, origin, mapa) == pos)
    return Up;
  else if (getMovement(Down, origin, mapa) == pos)
    return Down;
  return Idle;
}

// Obtém a direção de movimento a cada instante para o fantasma aleatório
Direction Fantasma::getMoveAleatorio(char mapa[ROWS][COLS], Position origin, Pacman pacman)
{
  Direction possibleDirections[4];
  int possibilities = 0;

  // Caso seja possível se mover numa direção, e ela não seja o contrário da direção atual, ela é adicionada como uma direção possível
  if (canMove(Left, pos, mapa) && dir != Right)
    // Caso esteja no início do jogo, como dir é "Idle", tem que checar startDir a fim de garantir que o fantasma não se mova na direção contrária
    if (!(isStart && startDir == Right))
      possibleDirections[possibilities++] = Left;
  if (canMove(Right, pos, mapa) && dir != Left)
    if (!(isStart && startDir == Left))
      possibleDirections[possibilities++] = Right;
  if (canMove(Down, pos, mapa) && dir != Up)
    possibleDirections[possibilities++] = Down;
  if (canMove(Up, pos, mapa) && dir != Down)
    possibleDirections[possibilities++] = Up;

  // Caminho sem saída: retorna por onde veio
  if (possibilities == 0)
  {
    if (dir == Left)
      return Right;
    else if (dir == Right)
      return Left;
    else if (dir == Down)
      return Up;
    else if (dir == Up)
      return Down;
  }

  // Escolhe uma direção aleatória
  int i;
  do
  {
    i = rand() % possibilities;
  } while (isStart && possibilities > 1 && possibleDirections[i] == dir); /*
    Caso seja o início do jogo, para forçar o fantasma a mudar de direção e sair do pátio, é aplicado o seguinte: caso haja mais de uma possibilidade de movimento, sorteia uma nova direção aleatória enquanto a direção sorteada for igual à direção atual.
  */
  if (isStart && possibilities > 1)
    isStart = false;
  return possibleDirections[i];
}

void Fantasma::draw(sf::RenderWindow *window)
{
  int frameWidth = textures[Right].getSize().x / totalFrames;
  int frameHeight = textures[Right].getSize().y;
  sf::IntRect frameRect(frameAtual * frameWidth, 0, frameWidth, frameHeight);
  sprite.setTextureRect(frameRect);
  sprite.setPosition(drawPos.x, drawPos.y);
  window->draw(sprite);
}
