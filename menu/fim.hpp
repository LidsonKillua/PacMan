#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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

private:
    sf::Music FraseFim;
    sf::Music MusicaFim;

public:
    Final(sf::RenderWindow *win, bool preso);
    ~Final();
    void run_menu();
    bool Reiniciar = false;

protected:
    void set_values(bool preso);
    void InitializeTxtReiniciar();
    void loop_events();
    void draw_all();
};
