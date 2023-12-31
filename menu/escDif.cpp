#ifdef _WIN32
#define WINDOWS_SYSTEM
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "escDif.hpp"
#include <iostream>

EscDif::EscDif(sf::RenderWindow* win)
{
    window = win;

    image = new sf::Texture();
    bg = new sf::Sprite();
    sdmenu = new sf::Sound;
    msmenu = new sf::SoundBuffer;

    set_values();
}

EscDif::~EscDif()
{
    for(auto b : btns)
        delete b;

    delete image;
    delete bg;
}

void EscDif::set_values()
{
    pos = 0;
    pressed = theselect = sair = false;
    image->loadFromFile("img/EscDif.png");
    bg->setTexture(*image);
    pos_mouse = {0, 0};
    mouse_coord = {0, 0};

    CorAmarela = sf::Color(255, 198, 0);
    CorSelecionado = sf::Color::Blue;

    options = {"EASY", "NORMAL", "HARD"};
    btns.resize(3);
    // Valores pegos no Gimp Ap�s desenhar os bot�es l�
    coords = {{332, 234}, {332, 340}, {332, 447}};
    sizes = {{532, 87}, {532, 87}, {532, 87}};

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
    if (!msmenu->loadFromFile("audio/musicamenu.wav"))
    {
        throw new GameError("Fatal Error: musicamenu load failed!");
        std::cout << "musicamenu load failed!";
    }

    sdmenu->setBuffer(*msmenu);
}

void EscDif::loop_events(){
    sf::Event event;
    while(window->pollEvent(event))
    {
        for(int i = 0; i<8; i++){
            bool Jpressed = sf::Joystick::isButtonPressed(0, i);

            if (Jpressed && !theselect)
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
            if(pos < 2)
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


        if(event.type == sf::Event::Closed)
        {
            window->close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !pressed)
        {
            if(pos < 2)
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
            sair = true;
        }

        pos_mouse = sf::Mouse::getPosition(*window);
        mouse_coord = window->mapPixelToCoords(pos_mouse);

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            for(std::size_t i{}; i < btns.size(); i++)
                if(btns[i]->getGlobalBounds().contains(mouse_coord))
                    RealizarTarefa(i);
                    sair = true;
        }
    }
}

void EscDif::draw_all()
{
    window->draw(*bg);


    cont++;
    // faz o bot�o selecionado piscar
    if(cont == 2000)
    {
        cont = 0;
        // se for amarelo muda pra preto, se n�o muda pra amarelo
        btns[pos]->setOutlineColor((btns[pos]->getOutlineColor() == CorAmarela)  ? CorSelecionado : CorAmarela);
    }


    for(auto b : btns)
        window->draw(*b);

    window->display();
}

Dificult EscDif::run_escDif(){
    // Play the sound
    sdmenu->play();

    while(!sair && window->isOpen())
    {
        loop_events();
        draw_all();
    }
    sdmenu->stop();

    return dificuldade;
}

void EscDif::RealizarTarefa(int option)
{
    switch(option)
    {
    case 0: dificuldade = Easy;
            break;

    case 1: dificuldade = Normal;
            break;

    case 2: dificuldade = Hard;
            break;
    }
}

void EscDif::Dormir(int ms){
    #ifdef WINDOWS_SYSTEM
      Sleep(ms);
    #else
      usleep(ms);
    #endif
}


