
#ifdef _WIN32
#define WINDOWS_SYSTEM
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "menu.hpp"
#include "sobre.hpp"
#include <iostream>

Menu::Menu(sf::RenderWindow* win)
{
    window = win;

    image = new sf::Texture();
    bg = new sf::Sprite();
    sdmenu = new sf::Sound;
    msmenu = new sf::SoundBuffer;

    CorAmarela = sf::Color(255, 198, 0);
    CorSelecionado = sf::Color::Blue;

    set_values();
}

Menu::~Menu()
{
    for(auto b : btns)
        delete b;

    delete image;
    delete bg;
}

void Menu::set_values()
{
    pos = 0;
    pressed = theselect = sair = false;
    image->loadFromFile("img/Menu.png");
    bg->setTexture(*image);
    pos_mouse = {0, 0};
    mouse_coord = {0, 0};

    options = {"CONTINUAR", "REINICIAR", "SOBRE", "SAIR"};
    btns.resize(4);
    // Valores pegos no Gimp Ap�s desenhar os bot�es l�
    coords = {{332, 176}, {332, 283}, {332, 390}, {332, 498}};
    sizes = {{532, 87}, {532, 87}, {532, 87}, {532, 87}};

    for(std::size_t i{}; i < btns.size(); i++)
    {
        btns[i] = new sf::RectangleShape();
        btns[i]->setSize(sizes[i]);
        btns[i]->setPosition(coords[i]);
        btns[i]->setOutlineColor(CorAmarela);
        btns[i]->setOutlineThickness(8);
        btns[i]->setFillColor(sf::Color::Transparent);
    }

    pos = 0;
    btns[0]->setOutlineColor(CorSelecionado);

    // Load it from a file
    if (!msmenu->loadFromFile(c_MscMenu))
    {
        throw new GameError(c_MscMenu);
    }

    sdmenu->setBuffer(*msmenu);
}

void Menu::loop_events()
{
    sf::Event event;
    while(window->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            window->close();
        }

        for(int i = 0; i<8; i++){
            bool Jpressed = sf::Joystick::isButtonPressed(0, i);

            if (Jpressed)
            {
                RealizarTarefa(pos);
                sair = true;
                break;
            }
        }

        if (sair) break;

        // xPosition < 0 : esquerda,
        // xPosition > 0 : direita
        float xPosition = sf::Joystick::getAxisPosition(0, sf::Joystick::X);

        // yPosition < 0 : cima,
        // yPosition > 0 : baixo
        float yPosition = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

        if (yPosition > Deadzone)
        {
            if(pos < 3)
            {
                pos++;
                btns[pos]->setOutlineColor(CorSelecionado);
                btns[pos - 1]->setOutlineColor(CorAmarela);
            }
            Dormir(500);
        }

        if (yPosition < -Deadzone)
        {
            if(pos > 0)
            {
                pos--;
                btns[pos]->setOutlineColor(CorSelecionado);
                btns[pos + 1]->setOutlineColor(CorAmarela);
            }
            Dormir(500);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            sair = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !pressed)
        {
            if(pos < 3)
            {
                pos++;
                pressed = true;
                btns[pos]->setOutlineColor(CorSelecionado);
                btns[pos - 1]->setOutlineColor(CorAmarela);
                pressed = false;
                theselect = false;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !pressed)
        {
            if(pos > 0)
            {
                pos--;
                pressed = true;
                btns[pos]->setOutlineColor(CorSelecionado);
                btns[pos + 1]->setOutlineColor(CorAmarela);
                pressed = false;
                theselect = false;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !theselect)
        {
            theselect = true;
            RealizarTarefa(pos);
        }

        pos_mouse = sf::Mouse::getPosition(*window);
        mouse_coord = window->mapPixelToCoords(pos_mouse);

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            for(std::size_t i{}; i < btns.size(); i++)
                if(btns[i]->getGlobalBounds().contains(mouse_coord))
                    RealizarTarefa(i);
        }
    }
}

void Menu::draw_all()
{
    window->draw(*bg);

    cont++;
    // faz o bot�o selecionado piscar
    if(cont == 2000)
    {
        cont = 0;
        // se for amarelo muda pra preto, se n�o muda pra amarelo
        btns[pos]->setOutlineColor((btns[pos]->getOutlineColor() == CorAmarela) ? CorSelecionado : CorAmarela);
    }

    for(auto b : btns)
        window->draw(*b);

    window->display();
}

void Menu::run_menu(int &ptsParaVencer)
{
    ptsEgg = ptsParaVencer;

    // Play the sound
    sdmenu->play();
    draw_all();
    Dormir(500);

    while(!sair && window->isOpen())
    {
        loop_events();
        draw_all();
    }

    sdmenu->stop();
    ptsParaVencer = ptsEgg;
    Dormir(500);
}

void Menu::RealizarTarefa(int option)
{
    switch(option)
    {
    case 0:
        sair = true;
        break;

    case 1:
        sair = true;
        Reiniciar = true;
        break;

    case 2:{
        Sobre *sobre = new Sobre(window);
        sobre->run_menu(ptsEgg);
        delete sobre;
        break;
    }

    case 3:
        window->close();
        break;
    }
}


void Menu::Dormir(int ms){
    #ifdef WINDOWS_SYSTEM
      Sleep(ms);
    #else
      usleep(1000);
    #endif
}
