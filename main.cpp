#include <iostream>
#include "game/game.hpp"
using namespace std;

int main()
{
    srand(time(0));
    while (true)
    {
        try
        {
            Game game;

            game.initialize();
            game.gameLoop();

            if (!game.Reiniciando)
                break;
        }
        catch (GameError error)
        {
            cout << error.msg << endl;
        }
    }

    return 0;
}
