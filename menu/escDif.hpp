#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class EscDif {
    int pos;
    bool pressed, theselect, sair;

    sf::RenderWindow * window;
    sf::RectangleShape * btnFacil;
    sf::RectangleShape * btnMedio;
    sf::RectangleShape * btnDificil;
    sf::Font * font;
    sf::Texture * image;
    sf::Sprite * bg;

    sf::Vector2i pos_mouse;
    sf::Vector2f mouse_coord;

    std::vector<const char *> options;
    std::vector<sf::Vector2f> coords;
    std::vector<sf::Text> texts;
    std::vector<std::size_t> sizes;

    protected:
        void set_values();
        void loop_events();
        void draw_all();

    public:
        EscDif(sf::RenderWindow* win);
        ~EscDif();
        void run_EscDif();
};

