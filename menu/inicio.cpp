#include "inicio.hpp"
#include <iostream>

Inicio::Inicio(sf::RenderWindow *win)
{
    window = win;

    imgT = new sf::Texture();
    imgS = new sf::Sprite();

    bgT = new sf::Texture();
    bgS = new sf::Sprite();

    set_values();
    InitializeTxtIniciar();
}

Inicio::~Inicio()
{
    delete imgT;
    delete imgS;
    delete bgT;
    delete bgS;
}

void Inicio::set_values()
{
    // imagem do inicio
    imgT->loadFromFile(c_ImgInicio);
    imgS->setTexture(*imgT);

    // Imagem de fundo: captura a imagem atual da tela
    bgT->create(window->getSize().x, window->getSize().y);
    bgT->update(*window);
    bgS->setTexture(*bgT);

    if (!MscInicio.openFromFile(c_MscIni))
        throw new ErroLeitura(c_MscIni);

    MscInicio.setVolume(50);
}

void Inicio::loop_events()
{
    sf::Event event;
    while (window->pollEvent(event)){
        if (event.type == sf::Event::Closed){
            window->close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
            sair = true;
        }
    }
}

void Inicio::draw_all()
{
    window->draw(*bgS);
    window->draw(*imgS);

    cont++;
    // faz o bot�o selecionado piscar
    if (cont == 2000)
    {
        cont = 0;
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
    txtIniciar.setPosition(sf::Vector2f(260, 567));
}

void Inicio::run_menu()
{
    MscInicio.play();

    while (!sair)
    {
        loop_events();
        draw_all();
    }
}
