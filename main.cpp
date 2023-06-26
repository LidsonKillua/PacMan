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

char mapa[11][21] =   // Mapa do jogo
{
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
    "11111111111111111111"
};

Pacman pacman =
{
intent :
    Idle,
dir :
    Idle,
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

void updateAnimation(float defTempo, float frameRate, int& frameAtual, int totalFrames, float& tempAcumul) //animação
{
    // Acumula o tempo decorrido
    tempAcumul += defTempo;

    // Atualiza a animação se o tempo acumulado for maior ou igual à taxa de atualização
    if (tempAcumul >= frameRate)
    {
        // Passa para o próximo frame
        frameAtual = (frameAtual + 1) % totalFrames;

        // Redefine o tempo acumulado
        tempAcumul = 0.0f;
    }
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

    // sprite do PacMan**********************************************************************************
    sf::Texture dir;
    if (!dir.loadFromFile("img/pac.png")) // ler imagem direita
    {
        std::cout << "Erro lendo imagem pac.png\n";
        return 0;
    }
    sf::Sprite sprite;
    sprite.setTexture(dir);
    sprite.setScale(sf::Vector2f(3.f, 3.f));

    sf::Texture esq;
    if (!esq.loadFromFile("img/pacesq.png")) // ler imagem esquerda
    {
        std::cout << "Erro lendo imagem pacesq.png\n";
        return 0;
    }

    sf::Texture down;
    if (!down.loadFromFile("img/pacdown.png")) // ler imagem esquerda
    {
        std::cout << "Erro lendo imagem pacdown.png\n";
        return 0;
    }
    sf::Texture up;
    if (!up.loadFromFile("img/pacup.png")) // ler imagem esquerda
    {
        std::cout << "Erro lendo imagem pacup.png\n";
        return 0;
    }
    //*************************************************************************************************
    // cria um relogio para medir o tempo do PacMan
    sf::Clock clock;

    // Animation Variables
    int frameAtual = 0;
    int totalFrames = 8; // Número total de frames na animação
    float frameRate = 0.01f; // Taxa de atualização da animação
    float tempAcumul = 0.0f;
    float defTempo = 1.0f;

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

        //***********************************************************
        // Muda a posição do PacMan a cada 0.2 segundos
        if (clock.getElapsedTime() > sf::seconds(0.2))
        {
            // tempo desde último restart > 0.2s?
            if (canMove(pacman.intent, pacman.posy, pacman.posx))
                pacman.dir = pacman.intent;
            if (canMove(pacman.dir, pacman.posy, pacman.posx))
            {
                if (pacman.dir == Left)
                {
                    sprite.setTexture(esq);
                    updateAnimation(defTempo, frameRate, frameAtual, totalFrames, tempAcumul);
                    pacman.posx--;
                }
                else if (pacman.dir == Right)
                {
                    sprite.setTexture(dir);
                    updateAnimation(defTempo, frameRate, frameAtual, totalFrames, tempAcumul);
                    pacman.posx++;
                }
                else if (pacman.dir == Up)
                {
                    sprite.setTexture(up);
                    updateAnimation(defTempo, frameRate, frameAtual, totalFrames, tempAcumul);
                    pacman.posy--;

                }
                else if (pacman.dir == Down)
                {
                    sprite.setTexture(down);
                    updateAnimation(defTempo, frameRate, frameAtual, totalFrames, tempAcumul);
                    pacman.posy++;
                }
            }

            ///////////////


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
        int frameWidth = dir.getSize().x / totalFrames;
        int frameHeight = dir.getSize().y;
        sf::IntRect frameRect(frameAtual * frameWidth, 0, frameWidth, frameHeight);
        sprite.setTextureRect(frameRect);
        sprite.setPosition(pacman.posx * SIZE, pacman.posy * SIZE);
        window.draw(sprite);

        // termina e desenha o frame corrente
        window.display();
    }
    return 0;
}
