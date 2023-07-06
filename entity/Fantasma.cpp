#include "fantasma.hpp"

bool Fantasma::initializeFantasmas(Fantasma fantasmas[])
{
  for (int i = 0; i < numFantasmas; i++)
  {
    fantasmas[i].dir = Idle;
    if (!fantasmas[i].texture.loadFromFile(c_ImgPolDir)) // ler imagem direita
    {
      throw new ErroLeitura(c_ImgPolDir);
      return false;
    }
    fantasmas[i].sprite.setTexture(fantasmas[i].texture);
    fantasmas[i].sprite.setScale(sf::Vector2f(1.1f, 1.1f));
  }
  fantasmas[0].pos.x = 1;
  fantasmas[0].pos.y = 1;
  fantasmas[0].tipo = Aleatorio;
  fantasmas[1].pos.x = 23;
  fantasmas[1].pos.y = 14;
  fantasmas[1].tipo = Perseguidor;
  return true;
}

// Função pra mover o fantasma, herdando de Entity
void Fantasma::move(char mapa[ROWS][COLS], Pacman pacman)
{
  // Caso o Pacman esteja parado (início de jogo), nada ocorre
  if (pacman.dir == Idle)
    return;
  Direction dir;
  if (tipo == Perseguidor)
    // Obtém a posição para onde deve se mover
    dir = getMovePerseguidor(mapa, pos, pacman);
  else
    dir = getMoveAleatorio(mapa, pos, pacman);

  // Move-se para essa direção
  pos = getMovement(dir, pos, mapa);
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
  Position pos;
  pos.x = number % COLS;
  pos.y = number / COLS;
  return pos;
}

/******************************************************************************
Função que realiza uma BFS no mapa até encontrar o Pacman, descobrindo assim o
menor caminho. Ela retorna a posição que corresponde ao primeiro movimento que o
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
    visited[u] = true;
    pos = numberToPos(u);
    // Vetor que armazena os vértices adjacentes
    vector<int> adjacents;

    // Ao encontrar o Pacman, encerra a busca
    if (pos == pacman.pos)
      break;

    /*
    Checa se Fantasma, a partir da posição atual, pode se mover para cada direção,
    e caso possa, adiciona o número de vértice correspondente à nova posição à lista de adjacentes.
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
      if (!visited[v])
      {
        visited[v] = true;
        /* Grava que o pai do nó adjacente "v" é "u", pois estamos acessando "v" a partir de "u"*/
        parent[v] = u;
        q.push(v);
      }
    }
  }
  // Se o Pacman está na mesma posição que o fantasma, o fantasma deve apenas ficar parado
  if (u == originV)
    return Idle;
  // Reconstrói o caminho até o nó cujo pai é o nó de origem (o primeiro movimento do Fantasma)
  while (parent[u] != originV)
  {
    u = parent[u];
  }
  // Traduz o número do vértice em posição no mapa, para saber pra qual posição o fantasma deve ir em seu primeiro movimento.
  pos = numberToPos(u);
  // De acordo com o deslocamento quanto ao ponto de origem, retorna a direção pra onde o fantasma deve se mover
  if (pos.x == origin.x - 1 || (origin.x == 0 && pos.x == COLS - 2))
    return Left;
  else if (pos.x == origin.x + 1 || (origin.x == COLS - 2 && pos.x == 0))
    return Right;
  else if (pos.y == origin.y - 1 || (origin.y == 0 && pos.y == ROWS - 1))
    return Up;
  else if (pos.y == origin.y + 1 || (origin.y == ROWS - 1 && pos.y == 0))
    return Down;
  return Idle;
}

Direction Fantasma::getMoveAleatorio(char mapa[ROWS][COLS], Position origin, Pacman pacman)
{
  srand(time(0));
  Direction possibleDirections[4];
  int possibilities = 0;
  if (canMove(Left, pos, mapa) && dir != Right)
    possibleDirections[possibilities++] = Left;
  if (canMove(Right, pos, mapa) && dir != Left)
    possibleDirections[possibilities++] = Right;
  if (canMove(Down, pos, mapa) && dir != Up)
    possibleDirections[possibilities++] = Down;
  if (canMove(Up, pos, mapa) && dir != Down)
    possibleDirections[possibilities++] = Up;
  if (possibilities > 1)
  {
    int i = rand() % possibilities;
    dir = possibleDirections[i];
  }
  else if (possibilities == 0)
  {
    if (dir == Left)
      dir = Right;
    else if (dir == Right)
      dir = Left;
    else if (dir == Down)
      dir = Up;
    else if (dir == Up)
      dir = Down;
  }
  else
    dir = possibleDirections[0];
  return dir;
}

void Fantasma::draw(sf::RenderWindow *window)
{
  sprite.setPosition(pos.x * SIZE, pos.y * SIZE);
  window->draw(sprite);
}
