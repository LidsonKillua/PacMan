#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "../globals/globals.hpp"

class EscDif{
    int pos, cont = 0;
    bool pressed, theselect, sair;
    Dificult dificuldade;

    sf::RenderWindow * window;
    sf::Texture * image;
    sf::Sprite * bg;

    sf::Vector2i pos_mouse;
    sf::Vector2f mouse_coord;

    std::vector<const char *> options;
    std::vector<sf::RectangleShape *> btns;
    std::vector<sf::Vector2f> coords;
    std::vector<sf::Vector2f> sizes;

    sf::SoundBuffer * msmenu;
    // Create a sound source
    sf::Sound * sdmenu;

    protected:
        void set_values();
        void loop_events();
        void draw_all();
        void RealizarTarefa(int option);

    public:
        EscDif(sf::RenderWindow* win);
        ~EscDif();
        Dificult run_escDif();
};
