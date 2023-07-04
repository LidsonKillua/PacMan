#include "menu.hpp"
#include <iostream>

Menu::Menu(sf::RenderWindow* win){
    window = win;

    font = new sf::Font();
    image = new sf::Texture();
    bg = new sf::Sprite();

    set_values();
}

Menu::~Menu(){
    for(auto b : btns)
        delete b;

    delete font;
    delete image;
    delete bg;
}

void Menu::set_values(){
    pos = 0;
    pressed = theselect = sair = false;
    font->loadFromFile("fonts/pacFont.TTF");
    image->loadFromFile("img/Menu.png");
    bg->setTexture(*image);
    pos_mouse = {0, 0};
    mouse_coord = {0, 0};

    options = {"CONTINUAR", "REINICIAR", "SOBRE", "SAIR"};
    btns.resize(4);
    coords = {{367, 165}, {367, 270}, {367, 375}, {367, 480}};
    sizes = {{546, 104}, {546, 104}, {546, 104}, {546, 104}};

    for(std::size_t i{}; i < btns.size(); i++){
        btns[i] = new sf::RectangleShape();
        btns[i]->setSize(sizes[i]);
        btns[i]->setPosition(coords[i]);
        btns[i]->setOutlineColor(sf::Color::Black);
        btns[i]->setFillColor(sf::Color::Transparent);
    }

    pos = 0;
    btns[0]->setOutlineThickness(3);
}

void Menu::loop_events(){
    sf::Event event;
    while(window->pollEvent(event)){
        if(event.type == sf::Event::Closed){
            window->close();
        }

        pos_mouse = sf::Mouse::getPosition(*window);
        mouse_coord = window->mapPixelToCoords(pos_mouse);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            sair = true;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !pressed){
            if(pos < 3){
                pos++;
                pressed = true;
                btns[pos]->setOutlineThickness(3);
                btns[pos - 1]->setOutlineThickness(0);
                pressed = false;
                theselect = false;
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !pressed){
            if(pos > 0){
                pos--;
                pressed = true;
                btns[pos]->setOutlineThickness(3);
                btns[pos + 1]->setOutlineThickness(0);
                pressed = false;
                theselect = false;
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !theselect){
            theselect = true;
            RealizarTarefa(pos);
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            for(std::size_t i{}; i < btns.size(); i++)
                if(btns[i]->getGlobalBounds().contains(mouse_coord))
                    RealizarTarefa(i);
        }
    }
}

void Menu::draw_all(){
    window->clear();
    window->draw(*bg);

    for(auto b : btns)
        window->draw(*b);

    window->display();
}

void Menu::run_menu(){
    while(!sair){
        loop_events();
        draw_all();
    }
}

void Menu::RealizarTarefa(int option){
    switch(option){
    case 0:
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        window->close();
        break;
    }
}
