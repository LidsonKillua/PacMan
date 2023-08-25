#include "inicio.hpp"
#include <iostream>
#include <string>
#include <string.h>

Inicio::Inicio(sf::RenderWindow *win)
{
    window = win;

    imgT = new sf::Texture();
    imgS = new sf::Sprite();

    set_values();
    InitializeTxtIniciar();
}

Inicio::~Inicio()
{
    delete imgT;
    delete imgS;
}

void Inicio::set_values()
{
    // imagem do inicio
    string indice = "00" + to_string(iImg);
    imgT->loadFromFile(c_ImgInicio + indice + ".jpg");
    imgS->setTexture(*imgT);

    if (!MscInicio.openFromFile(c_MscIni))
        throw new ErroLeitura(c_MscIni);

    MscInicio.setVolume(50);
}

void Inicio::atualizarImg()
{
    string indice = (iImg > 99 ? to_string(iImg) : (iImg > 9 ? "0" + to_string(iImg) : "00" + to_string(iImg)));
    imgT->loadFromFile(c_ImgInicio + indice + ".jpg");

    if(iImg >= 299)
        iImg = 0;
    else
        iImg++;
}

void Inicio::loop_events()
{
    for(int i = 0; i<8; i++){
        bool Jpressed = sf::Joystick::isButtonPressed(0, i);

        if (Jpressed){
            sair = true;
            break;
        }
    }

    sf::Event event;
    while (window->pollEvent(event)){
        if (event.type == sf::Event::Closed){
            window->close();
        }

        // Por enquanto o enter do Fliperama vai ser joystick a direita(n�o sei o outro bot�o)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
            sair = true;
        }
    }
}

void Inicio::draw_all()
{
    window->draw(*imgS);

    // piscar o texto
    if (iImg % 6 == 0){
        desenharTxt = !desenharTxt;
    }

    if (desenharTxt)
        window->draw(txtIniciar);

    window->display();
}

void Inicio::InitializeTxtIniciar()
{
    font = new sf::Font();
    font->loadFromFile("fonts/emulogic.ttf");

    txtIniciar.setFont(*font);
    txtIniciar.setString("PRESS ENTER TO PLAY");
    txtIniciar.setCharacterSize(25);
    txtIniciar.setPosition(sf::Vector2f(363, 567));
}

void Inicio::run_menu()
{
    MscInicio.play();

    while (!sair)
    {
        loop_events();
        atualizarImg();
        draw_all();
    }
}
