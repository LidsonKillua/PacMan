#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../globals/globals.hpp"

class Menu {
    int pos, cont = 0;
    bool pressed, theselect, sair;

    sf::RenderWindow * window;
    sf::Texture * image;
    sf::Sprite * bg;

    sf::Vector2i pos_mouse;
    sf::Vector2f mouse_coord;

    std::vector<const char *> options;
    std::vector<sf::RectangleShape *> btns;
    std::vector<sf::Vector2f> coords;
    std::vector<sf::Vector2f> sizes;

    protected:
        void set_values();
        void loop_events();
        void draw_all();
        void RealizarTarefa(int option);

    public:
        Menu(sf::RenderWindow* win);
        ~Menu();
        void run_menu();
        bool Reiniciar = false;
};
