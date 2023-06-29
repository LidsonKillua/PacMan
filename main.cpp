#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>
using namespace std;

#define SIZE 50        // Tamanho de cada c�lula do mapa
#define numFantasmas 1 // Alterar a Quantidade de Fantasmas
#define qtdPilulas 20  // Alterar a Quantidade de Pilulas
int pontos = 0;

// Dire��o do Pacman ou Fantasmas
enum Direction
{
    Left,
    Right,
    Up,
    Down,
    Idle
};

struct Position
{
    int x;
    int y;
};

// Struct de Entity (seja Pacman ou fantasma)
struct Entity
{

    sf::Sprite sprite;
    map<Direction, sf::Texture> textures;
    Direction intent;
    Direction dir;
    Position pos;
};

char mapa[11][21] = // Mapa do jogo
    {
        "11111111111111111111",
        "10000100222220100001",
        "10110101111110101101",
        "10100222222222200101",
        "10101101100110110101",
        "10000001000010000001",
        "10101101111110110101",
        "10100000002000000101",
        "10110101111110101101",
        "10000100222200100001",
        "11111111111111111111"};

Entity pacman;
Entity fantasmas[numFantasmas];

bool canMove(Entity e)
{
    if (e.dir == Up)
    {
        if (mapa[e.pos.y - 1][e.pos.x] != '1')
            return true;
    }
    else if (e.dir == Down)
    {
        if (mapa[e.pos.y + 1][e.pos.x] != '1')
            return true;
    }
    else if (e.dir == Left)
    {
        if (mapa[e.pos.y][e.pos.x - 1] != '1')
            return true;
    }
    else if (e.dir == Right)
    {
        if (mapa[e.pos.y][e.pos.x + 1] != '1')
            return true;
    }
    return false;
}

void updateAnimation(float defTempo, float frameRate, int &frameAtual, int totalFrames, float &tempAcumul) // anima��o
{
    // Acumula o tempo decorrido
    tempAcumul += defTempo;

    // Atualiza a anima��o se o tempo acumulado for maior ou igual � taxa de atualiza��o
    if (tempAcumul >= frameRate)
    {
        // Passa para o pr�ximo frame
        frameAtual = (frameAtual + 1) % totalFrames;

        // Redefine o tempo acumulado
        tempAcumul = 0.0f;
    }
}

// Inicializa o PacMan
bool initializePacman()
{
    pacman.dir = Idle;
    pacman.intent = Idle;
    pacman.pos.x = 9;
    pacman.pos.y = 7;
    if (!pacman.textures[Right].loadFromFile("img/pac.png")) // ler imagem direita
    {
        std::cout << "Erro lendo imagem pac.png\n";
        return false;
    }
    pacman.sprite.setTexture(pacman.textures[Right]);
    pacman.sprite.setScale(sf::Vector2f(3.f, 3.f));

    if (!pacman.textures[Left].loadFromFile("img/pacesq.png")) // ler imagem esquerda
    {
        std::cout << "Erro lendo imagem pacesq.png\n";
        return false;
    }

    if (!pacman.textures[Down].loadFromFile("img/pacdown.png")) // ler imagem esquerda
    {
        std::cout << "Erro lendo imagem pacdown.png\n";
        return false;
    }

    if (!pacman.textures[Up].loadFromFile("img/pacup.png")) // ler imagem esquerda
    {
        std::cout << "Erro lendo imagem pacup.png\n";
        return false;
    }
    return true;
}

// Inicializa os Fantasmas
bool initializeFantasmas()
{
    for (int i = 0; i < numFantasmas; i++)
    {
        fantasmas[i].dir = Idle;
        fantasmas[i].intent = Idle;
        fantasmas[i].pos.x = 1;
        fantasmas[i].pos.y = 1;
        if (!fantasmas[i].textures[Right].loadFromFile("img/ghost.png")) // ler imagem direita
        {
            std::cout << "Erro lendo imagem ghost.png\n";
            return false;
        }
        fantasmas[i].sprite.setTexture(fantasmas[i].textures[Right]);
    }
    return true;
}

Direction getMinPathToPacman(int posx, int posy)
{
    queue<Position> q;
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

    // Inicializa o Pacman
    if (!initializePacman())
        return 0;

    // Inicializa os Fantasmas
    if (!initializeFantasmas())
        return 0;
    //*************************************************************************************************
    // cria um relogio para medir o tempo do PacMan
    sf::Clock clock;

    // Animation Variables
    int frameAtual = 0;
    int totalFrames = 8;     // N�mero total de frames na anima��o
    float frameRate = 0.01f; // Taxa de atualiza��o da anima��o
    float tempAcumul = 0.0f;
    float defTempo = 1.0f;

    // executa o programa enquanto a janela est� aberta
    while (window.isOpen())
    {

        // verifica todos os eventos que foram acionados na janela desde a �ltima itera��o do loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // evento "fechar" acionado: fecha a janela
            if (event.type == sf::Event::Closed)
                window.close();
            // tecla pressionada

            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                    break;
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

        //***********************************************************
        // Muda a posi��o do PacMan a cada 0.2 segundos
        if (clock.getElapsedTime() > sf::seconds(0.2))
        {
            // tempo desde �ltimo restart > 0.2s?
            if (canMove(pacman))
                pacman.dir = pacman.intent;
            if (canMove(pacman))
            {
                if (pacman.dir == Left)
                {
                    pacman.sprite.setTexture(pacman.textures[Left]);
                    updateAnimation(defTempo, frameRate, frameAtual, totalFrames, tempAcumul);
                    pacman.pos.x--;
                }
                else if (pacman.dir == Right)
                {
                    pacman.sprite.setTexture(pacman.textures[Right]);
                    updateAnimation(defTempo, frameRate, frameAtual, totalFrames, tempAcumul);
                    pacman.pos.x++;
                }
                else if (pacman.dir == Up)
                {
                    pacman.sprite.setTexture(pacman.textures[Up]);
                    updateAnimation(defTempo, frameRate, frameAtual, totalFrames, tempAcumul);
                    pacman.pos.y--;
                }
                else if (pacman.dir == Down)
                {
                    pacman.sprite.setTexture(pacman.textures[Down]);
                    updateAnimation(defTempo, frameRate, frameAtual, totalFrames, tempAcumul);
                    pacman.pos.y++;
                }
            }

            ///////////////

            if (mapa[pacman.pos.y][pacman.pos.x] == '2')
            {
                mapa[pacman.pos.y][pacman.pos.x] = '0';
                pontos++;
                cout << "PONTOS: " << pontos << endl;

                if (pontos == qtdPilulas)
                    cout << "Voce Venceu!" << endl;
            }

            clock.restart(); // recome�a contagem do tempo
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
        int frameWidth = pacman.textures[Right].getSize().x / totalFrames;
        int frameHeight = pacman.textures[Right].getSize().y;
        sf::IntRect frameRect(frameAtual * frameWidth, 0, frameWidth, frameHeight);
        pacman.sprite.setTextureRect(frameRect);
        pacman.sprite.setPosition(pacman.pos.x * SIZE, pacman.pos.y * SIZE);
        window.draw(pacman.sprite);

        // desenha Fantasmas
        for (int i = 0; i < numFantasmas; i++)
        {
            fantasmas[i].sprite.setPosition(fantasmas[i].pos.x * SIZE, fantasmas[i].pos.y * SIZE);
            window.draw(fantasmas[i].sprite);
        }

        // termina e desenha o frame corrente
        window.display();
    }
    return 0;
}
