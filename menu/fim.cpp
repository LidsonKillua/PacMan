#include "fim.hpp"
#include <iostream>

Final::Final(sf::RenderWindow* win, bool preso){
    window = win;

    image = new sf::Texture();
    bg = new sf::Sprite();

    set_values(preso);
    InitializeTxtReiniciar();
}

Final::~Final(){
    delete image;
    delete bg;
}

void Final::set_values(bool preso){
    sair = false;

    // pega a imagem de win se não foi preso
    cout << preso;
    image->loadFromFile(preso ? "img/wasted.png" : "img/win.png");

    bg->setTexture(*image);
}

void Final::loop_events(){
    sf::Event event;
    while(window->pollEvent(event)){
        if(event.type == sf::Event::Closed){
            window->close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
            sair = true;
            Reiniciar = true;
        }
    }
}

void Final::draw_all(){
    window->draw(*bg);

    cont++;
    // faz o botão selecionado piscar
    if(cont == 2000){
        cont = 0;
        desenharTxt = !desenharTxt;
    }

    if(desenharTxt)
        window->draw(txtReiniciar);

    window->display();
}

void Final::InitializeTxtReiniciar(){
  font = new sf::Font();
  font->loadFromFile("fonts/emulogic.ttf");

  txtReiniciar.setFont(*font);
  txtReiniciar.setString("PRESS ENTER TO TITLE SCREEN");
  txtReiniciar.setCharacterSize(25);
  txtReiniciar.setPosition(sf::Vector2f(260, 567));
}

void Final::run_menu(){
    while(!sair){
        loop_events();
        draw_all();
    }
}
