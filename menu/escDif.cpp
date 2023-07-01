#include "escDif.hpp"

EscDif::EscDif(sf::RenderWindow* win){
    window = win;
    btnFacil = new sf::RectangleShape();
    btnMedio = new sf::RectangleShape();
    btnDificil = new sf::RectangleShape();

    font = new sf::Font();
    image = new sf::Texture();
    bg = new sf::Sprite();

    set_values();
}

EscDif::~EscDif(){
    delete btnFacil;
    delete btnMedio;
    delete btnDificil;

    delete font;
    delete image;
    delete bg;
}

void EscDif::set_values(){
    pos = 0;
    pressed = theselect = sair = false;
    font->loadFromFile("fonts/PAC-FONT.ttf");
    image->loadFromFile("img/EscDif.png");
    bg->setTexture(*image);
    pos_mouse = {0, 0};
    mouse_coord = {0, 0};
}

void EscDif::loop_events(){
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

void EscDif::draw_all(){
    window->clear();
    window->draw(*bg);
    window->display();
}

void EscDif::run_EscDif(){
    while(!sair){
        loop_events();
        draw_all();
    }
}

