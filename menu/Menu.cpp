#include "menu.hpp"

Menu::Menu(sf::RenderWindow* win){
    window = win;
    winclose = new sf::RectangleShape();
    font = new sf::Font();
    image = new sf::Texture();
    bg = new sf::Sprite();

    set_values();
}

Menu::~Menu(){
    delete winclose;
    delete font;
    delete image;
    delete bg;
}

void Menu::set_values(){
    //window->create(sf::VideoMode(1280,720), "Menu", sf::Style::Titlebar | sf::Style::Close);
    //window->setPosition(sf::Vector2i(0, 0));

    pos = 0;
    pressed = theselect = sair = false;
    font->loadFromFile("fonts/PAC-FONT.ttf");
    image->loadFromFile("img/Menu.png");
    bg->setTexture(*image);
    pos_mouse = {0, 0};
    mouse_coord = {0, 0};
}

void Menu::loop_events(){
    sf::Event event;
    while(window->pollEvent(event)){
        if(event.type == sf::Event::Closed){
            window->close();
        }
        else if (event.type == sf::Event::KeyPressed){
            if (event.key.code == sf::Keyboard::Escape){
                    sair = true;
            }
        }
    }
}

void Menu::draw_all(){
    window->clear();
    window->draw(*bg);
    window->display();
}

void Menu::run_menu(){
    while(!sair){
        loop_events();
        draw_all();
    }
}
