#include <iostream>
#include "game/game.hpp"
using namespace std;

int main()
{
    Game game;

    try
    {
        game.gameLoop();
    }
    catch (GameError error)
    {
        cout << error.msg << endl;
    }

    return 0;
}
