#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>
#include "menu/menu.hpp"
#include "globals/globals.hpp"
#include "entity/pacman.hpp"
#include "entity/fantasma.hpp"
using namespace std;

#define SIZE 48        // Tamanho de cada c�lula do mapa
#define numFantasmas 1 // Alterar a Quantidade de Fantasmas
#define qtdPilulas 30  // Alterar a Quantidade de Pilulas
const int TAMX = 1200; // Tamanho da Janela
const int TAMY = 768;  // Tamanho da Janela
int pontos = 0;

char mapa[ROWS][COLS] = // Mapa do jogo
    {
        "1111111111110111111111111",
        "1000000000000000000000001",
        "1011011111110111111101101",
        "1011011111110111111101101",
        "1000000000000000000000001",
        "1011111110111110111111101",
        "0002222222222222222222000",
        "1011101111110111111011101",
        "1000001000000000001000001",
        "1011101111110111111011101",
        "1000100222222222220010001",
        "1110111010111110101110111",
        "1000000010000000100000001",
        "1011111111110111111111101",
        "1000000000000000000000001",
        "1111111111110111111111111"};

Pacman pacman;
Fantasma fantasmas[numFantasmas];

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
    pacman.pos.x = 12;
    pacman.pos.y = 8;
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
        if (!fantasmas[i].textures[Right].loadFromFile("img/ghost.png")) // ler imagem direita
        {
            std::cout << "Erro lendo imagem ghost.png\n";
            return false;
        }
        fantasmas[i].sprite.setTexture(fantasmas[i].textures[Right]);
    }
    fantasmas[0].pos.x = 1;
    fantasmas[0].pos.y = 1;
    return true;
}

int main()
{
    /*Menu * menu = new Menu();
    menu->run_menu();
    delete menu;*/
    // menu = nullptr;

    // cria a janela
    sf::RenderWindow window(sf::VideoMode(TAMX, TAMY), "Pac-Man");

    // background
    sf::RectangleShape backgd(sf::Vector2f(TAMX, TAMY));
    sf::Texture fd;
    if (!fd.loadFromFile("img/map.png"))
    {
        cout << "Fatal Error" << endl;
        return 0;
    }
    sf::Sprite background(fd);

    // shape da parede
    sf::RectangleShape rectangle(sf::Vector2f(SIZE, SIZE));
    rectangle.setFillColor(sf::Color(255, 255, 255, 256)); // rectangle transparente
    rectangle.setOutlineThickness(-5);
    rectangle.setOutlineColor(sf::Color(255, 255, 255, 256)); // rectangle border transparente

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
                if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::P)
                {
                    Menu *menu = new Menu(&window);
                    menu->run_menu();
                    delete menu;
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

            // MOVE FANTASMAS
            for (int i = 0; i < numFantasmas; i++)
            {
                fantasmas[i].move(mapa, pacman);
            }

            // MOVE PACMAN
            pacman.move(mapa);
            if (pacman.canMove(pacman.dir, pacman.pos, mapa))
            {
                updateAnimation(defTempo, frameRate, frameAtual, totalFrames, tempAcumul);
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

        window.draw(background); // desenha o mapa no fundo da tela

        for (int i = 0; i < ROWS; i++)
            for (int j = 0; j < COLS; j++)
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
