#include "fim.hpp"
#include <iostream>

Final::Final(sf::RenderWindow *win, bool preso)
{
    window = win;

    imgT = new sf::Texture();
    imgS = new sf::Sprite();

    bgT = new sf::Texture();
    bgS = new sf::Sprite();

    set_values(preso);
    InitializeTxtReiniciar();
}

Final::~Final()
{
    delete imgT;
    delete imgS;
    delete bgT;
    delete bgS;
}

void Final::set_values(bool preso)
{
    sair = false;

    // pega a imgTm de win se n�o foi preso
    imgT->loadFromFile(preso ? "img/wasted.png" : "img/win.png");
    imgS->setTexture(*imgT);

    // Imagem de fundo: captura a imagem atual da tela
    bgT->create(window->getSize().x, window->getSize().y);
    bgT->update(*window);
    bgS->setTexture(*bgT);


    srand(time(0));
    int i = 0;

    if(preso){
        i = rand() % qtdFalasD;
        if (!FraseFim.openFromFile(falas_FinaisD[i]))
            throw new ErroLeitura(falas_FinaisD[i]);

        i = rand() % qtdMscD;
        if (!MusicaFim.openFromFile(audios_FinaisD[i]))
            throw new ErroLeitura(audios_FinaisD[i]);
    }
    else{
        i = rand() % qtdFalasV;
        if (!FraseFim.openFromFile(falas_FinaisV[i]))
            throw new ErroLeitura(falas_FinaisV[i]);

        i = rand() % qtdMscV;
        if (!MusicaFim.openFromFile(audios_FinaisV[i]))
            throw new ErroLeitura(audios_FinaisV[i]);
    }

    FraseFim.setVolume(30);
    MusicaFim.setVolume(20);
}

void Final::loop_events()
{
    for(int i = 0; i<8; i++){
        bool Jpressed = sf::Joystick::isButtonPressed(0, i);

        if (Jpressed){
            sair = true;
            Reiniciar = true;
            break;
        }
    }

    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window->close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            sair = true;
            Reiniciar = true;
        }
    }
}

void Final::draw_all()
{
    window->draw(*bgS);
    window->draw(*imgS);

    cont++;
    // faz o bot�o selecionado piscar
    if (cont == 2000)
    {
        cont = 0;
        desenharTxt = !desenharTxt;
    }

    if (desenharTxt)
        window->draw(txtReiniciar);

    window->display();
}

void Final::InitializeTxtReiniciar()
{
    font = new sf::Font();
    font->loadFromFile("fonts/emulogic.ttf");

    txtReiniciar.setFont(*font);
    txtReiniciar.setString("PRESS ENTER TO TITLE SCREEN");
    txtReiniciar.setCharacterSize(25);
    txtReiniciar.setPosition(sf::Vector2f(260, 567));
}

void Final::run_menu()
{
    FraseFim.setVolume(20);
    MusicaFim.setVolume(15);
    FraseFim.play();
    MusicaFim.play();

    while (!sair)
    {
        loop_events();
        draw_all();
    }
}
