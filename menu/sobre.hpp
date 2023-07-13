#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "../globals/globals.hpp"

class Sobre
{
    bool sair = false, desenharTxt = true;
    int iImg = 0;

    sf::Vector2i pos_mouse;
    sf::Vector2f mouse_coord;

    sf::RenderWindow *window;
    sf::Texture *imgT;
    sf::Sprite *imgS;
    sf::Text txtIniciar;
    sf::Font *font;
    sf::RectangleShape *egg; //easter egg

private:
    sf::Music AudioLadrao;

public:
    Sobre(sf::RenderWindow *win);
    ~Sobre();
    void run_menu(int &ptsEgg);

protected:
    void set_values();
    void InitializeTxtIniciar();
    void loop_events(int &ptsEgg);
    void draw_all();
};

