#include "menu.hpp"
#include <iostream>

Menu::Menu(sf::RenderWindow* win){
    window = win;

    btnContinuar = new sf::RectangleShape();
    btnReiniciar = new sf::RectangleShape();
    btnSobre = new sf::RectangleShape();
    btnSair = new sf::RectangleShape();

    font = new sf::Font();
    image = new sf::Texture();
    bg = new sf::Sprite();

    set_values();
}

Menu::~Menu(){
    delete btnContinuar;
    delete btnReiniciar;
    delete btnSobre;
    delete btnSair;

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

    options = {"PAc CRIME", "CONTINUAR", "REINICIAR", "SOBRE", "SAIR"};
    texts.resize(5);
    coords = {{402, 47}, {392, 185}, {410, 292}, {499, 400}, {543, 510}};
    sizes = {62, 62, 62, 62, 62};

    for(std::size_t i{}; i < texts.size(); i++){
        texts[i].setFont(*font);
        texts[i].setString(options[i]);
        texts[i].setCharacterSize(sizes[i]);
        texts[i].setOutlineColor(sf::Color::Black);
        texts[i].setOutlineThickness(3);
        texts[i].setColor(sf::Color::Yellow);
        texts[i].setPosition(coords[i]);
    }

    btnContinuar->setSize(sf::Vector2f(546, 104));
    btnReiniciar->setSize(sf::Vector2f(546, 104));
    btnSobre->setSize(sf::Vector2f(546, 104));
    btnSair->setSize(sf::Vector2f(546, 104));

    btnContinuar->setPosition(sf::Vector2f(367, 165));
    btnReiniciar->setPosition(sf::Vector2f(367, 270));
    btnSobre->setPosition(sf::Vector2f(367, 375));
    btnSair->setPosition(sf::Vector2f(367, 480));

    btnContinuar->setFillColor(sf::Color::Transparent);
    btnReiniciar->setFillColor(sf::Color::Transparent);
    btnSobre->setFillColor(sf::Color::Transparent);
    btnSair->setFillColor(sf::Color::Transparent);

    texts[1].setOutlineColor(sf::Color::Yellow);
    pos = 1;
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
            if(pos < 4){
                pos++;
                pressed = true;
                texts[pos].setOutlineThickness(2);
                texts[pos - 1].setOutlineThickness(4);
                pressed = false;
                theselect = false;
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !pressed){
            if(pos > 1){
                pos--;
                pressed = true;
                texts[pos].setOutlineThickness(2);
                texts[pos + 1].setOutlineThickness(4);
                pressed = false;
                theselect = false;
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !theselect){
            theselect = true;
            std::cout << options[pos] << std::endl;
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if(btnContinuar->getGlobalBounds().contains(mouse_coord)){
                std::cout << options[1] << std::endl;
            }
        }
    }
}

void Menu::draw_all(){
    window->clear();
    window->draw(*bg);

    for(auto t : texts){
        window->draw(t);
    }

    window->display();
}

void Menu::run_menu(){
    while(!sair){
        loop_events();
        draw_all();
    }
}
