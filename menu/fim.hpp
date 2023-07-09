#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../globals/globals.hpp"

class Final
{
    bool sair, desenharTxt = true;
    int cont = 0;

    sf::RenderWindow *window;
    sf::Texture *imgT;
    sf::Texture *bgT;
    sf::Sprite *imgS;
    sf::Sprite *bgS;
    sf::Text txtReiniciar;
    sf::Font *font;

protected:
    void set_values(bool preso);
    void InitializeTxtReiniciar();
    void loop_events();
    void draw_all();

public:
    Final(sf::RenderWindow *win, bool preso);
    ~Final();
    void run_menu();
    bool Reiniciar = false;
};
