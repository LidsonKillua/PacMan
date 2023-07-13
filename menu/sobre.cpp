// usar sleep

#ifdef _WIN32
#define WINDOWS_SYSTEM
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "sobre.hpp"
#include <iostream>
#include <string>
#include <string.h>

Sobre::Sobre(sf::RenderWindow *win)
{
    window = win;

    imgT = new sf::Texture();
    imgS = new sf::Sprite();
    egg = new sf::RectangleShape();

    set_values();
    InitializeTxtIniciar();
}

Sobre::~Sobre()
{
    delete imgT;
    delete imgS;
    delete egg;
}

void Sobre::set_values()
{
    imgT->loadFromFile(c_ImgSobre);
    imgS->setTexture(*imgT);

    if (!AudioLadrao.openFromFile(c_AudioLadrao))
        throw new ErroLeitura(c_AudioLadrao);

    AudioLadrao.setVolume(50);

    pos_mouse = {0, 0};
    mouse_coord = {0, 0};

    egg->setSize(sf::Vector2f(107, 170));
    egg->setPosition(sf::Vector2f(581, 473));
    egg->setFillColor(sf::Color::Transparent);
}

void Sobre::loop_events(int &ptsEgg)
{
    sf::Event event;
    while (window->pollEvent(event)){
        if (event.type == sf::Event::Closed){
            window->close();
        }

        pos_mouse = sf::Mouse::getPosition(*window);
        mouse_coord = window->mapPixelToCoords(pos_mouse);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            sair = true;
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if(egg->getGlobalBounds().contains(mouse_coord)){
                ptsEgg = 50; // Hack para precisar de menos pontos para vencer
                sair = true;
            }
        }
    }
}

void Sobre::draw_all()
{
    window->draw(*imgS);
    window->draw(*egg);

    iImg++;
    // piscar o texto
    if (iImg == 2000){
        iImg = 0;
        desenharTxt = !desenharTxt;
    }

    if (desenharTxt)
        window->draw(txtIniciar);

    window->draw(txtSobre);

    window->display();
}

void Sobre::InitializeTxtIniciar()
{
    font = new sf::Font();
    font->loadFromFile("fonts/emulogic.ttf");

    txtIniciar.setFont(*font);
    txtIniciar.setString("PRESS ESC TO CLOSE");
    txtIniciar.setCharacterSize(25);
    txtIniciar.setPosition(sf::Vector2f(363, 667));

    txtSobre.setFont(*font);
    txtSobre.setString("Thierry Stofel  Lidson Oliveira  Joao Vitor Melo");
    txtSobre.setCharacterSize(20);
    txtSobre.setOutlineColor(sf::Color::Black);
    txtSobre.setOutlineThickness(3);
    txtSobre.setPosition(sf::Vector2f(50, 30));
}

void Sobre::run_menu(int &ptsEgg)
{
    while (!sair)
    {
        loop_events(ptsEgg);
        draw_all();
    }

    if (ptsEgg == 50){
        AudioLadrao.play();

        #ifdef WINDOWS_SYSTEM
          Sleep( 2000 );
        #else
          usleep( 2000 );
        #endif

        AudioLadrao.stop();
    }
}

