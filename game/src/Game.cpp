#include "Game.h"
#include <iostream>

using namespace std;

Game::Game(const char* configfile) : PhantomGame(configfile) {
    cout << "It works! And that is an assumption. -- Gerjo" << endl;

    pushGameState(&_gameState);

    Soldier* soldier = new Soldier();
    _gameState.addComponent(soldier);

    Composite* composite = new Composite();
    Graphics* gfx = composite->getGraphics();
    gfx->beginPath();
    gfx->setFillStyle(Color(127, 127, 127, 127));
    gfx->image("Tank Bot.png", 0, 0, 281, 335);
    gfx->beginPath();

    soldier->addComponent(composite);
}
