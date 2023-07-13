#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "../globals/globals.hpp"

class Inicio
{
    bool sair = false, desenharTxt = true;
    int cont = 0, iImg = 0;

    sf::RenderWindow *window;
    sf::Texture *imgT;
    sf::Sprite *imgS;
    sf::Text txtIniciar;
    sf::Font *font;

private:
    sf::Music MscInicio;

public:
    Inicio(sf::RenderWindow *win);
    ~Inicio();
    void run_menu();

protected:
    void set_values();
    void InitializeTxtIniciar();
    void loop_events();
    void atualizarImg();
    void draw_all();
};
