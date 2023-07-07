#include "menu.hpp"
#include <iostream>

Menu::Menu(sf::RenderWindow* win)
{
    window = win;

    image = new sf::Texture();
    bg = new sf::Sprite();

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
    // Valores pegos no Gimp Após desenhar os botões lá
    coords = {{332, 176}, {332, 283}, {332, 390}, {332, 498}};
    sizes = {{532, 87}, {532, 87}, {532, 87}, {532, 87}};

    for(std::size_t i{}; i < btns.size(); i++)
    {
        btns[i] = new sf::RectangleShape();
        btns[i]->setSize(sizes[i]);
        btns[i]->setPosition(coords[i]);
        btns[i]->setOutlineColor(sf::Color::Yellow);
        btns[i]->setOutlineThickness(8);
        btns[i]->setFillColor(sf::Color::Transparent);
    }

    pos = 0;
    btns[0]->setOutlineColor(sf::Color::Black);
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

        pos_mouse = sf::Mouse::getPosition(*window);
        mouse_coord = window->mapPixelToCoords(pos_mouse);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            sair = true;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !pressed)
        {
            if(pos < 3)
            {
                pos++;
                pressed = true;
                btns[pos]->setOutlineColor(sf::Color::Black);//->setOutlineThickness(3);
                btns[pos - 1]->setOutlineColor(sf::Color::Yellow);//->setOutlineThickness(0);
                pressed = false;
                theselect = false;
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !pressed)
        {
            if(pos > 0)
            {
                pos--;
                pressed = true;
                btns[pos]->setOutlineColor(sf::Color::Black);//->setOutlineThickness(3);
                btns[pos + 1]->setOutlineColor(sf::Color::Yellow);//->setOutlineThickness(0);
                pressed = false;
                theselect = false;
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !theselect)
        {
            theselect = true;
            RealizarTarefa(pos);
        }

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
    // faz o botão selecionado piscar
    if(cont == 2000)
    {
        cont = 0;
        // se for amarelo muda pra preto, se não muda pra amarelo
        btns[pos]->setOutlineColor((btns[pos]->getOutlineColor() == sf::Color::Yellow)  ? sf::Color::Black : sf::Color::Yellow);
    }


    for(auto b : btns)
        window->draw(*b);

    window->display();
}

void Menu::run_menu()
{
    sf::SoundBuffer msmenu;

    // Load it from a file
    if (!msmenu.loadFromFile("audio/musicamenu.wav"))
    {
        std::cout << "musicamenu load failed!";
    }

    // Create a sound source and bind it to the buffer
    sf::Sound sdmenu;
    sdmenu.setBuffer(msmenu);
    sdmenu.play();

    // Play the sound
    while(!sair)
    {
        loop_events();
        draw_all();
    }
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
    case 2:
        break;
    case 3:
        window->close();
        break;
    }
}
