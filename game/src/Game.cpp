#include "Game.h"
#include <iostream>

using namespace std;

Game::Game(const char* configfile) : PhantomGame(configfile) {
    cout << "It works! And that is an assumption. -- Gerjo" << endl;

    _gameState.addComponent(&_tiles);
    _gameState.addComponent(&_cursorlayer);
    pushGameState(&_gameState);

    int tileSize = 12;
    int width    = getWidth();
    int height   = getHeight();
    _tiles.createTiles(tileSize, (int)(width / tileSize), (int)(height / tileSize));

    for(int x = 0; x < width; x += tileSize) {
        for(int y = 0; y < height; y += tileSize) {
            Ground* ground = new Ground();

            ground->setX(static_cast<float>(x));
            ground->setY(static_cast<float>(y));

            _tiles.addComponent(ground);
        }
    }

    _tiles.addComponent(new Soldier());

    _cursorlayer.addComponent(&_selector);



}
