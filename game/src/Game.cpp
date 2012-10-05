#include "Game.h"
#include <iostream>
#include "RtsCamera.h"


using namespace std;

Game::Game(const char* configfile) : PhantomGame(configfile) {
    setDriver(new GLUTDriver(this));
    cout << "It works! And that is an assumption. -- Gerjo" << endl;

    RtsCamera* cam = new RtsCamera();
    _cursorlayer.addComponent(cam);


    _cursorlayer.addComponent(&_selector);
    _gameState.addComponent(&_tiles);
    _gameState.addComponent(&_cursorlayer);
    pushGameState(&_gameState);

    int tileSize = 12;
    int width    = getWidth();
    int height   = getHeight();
    _tiles.createTiles(tileSize, (int)floor(width / tileSize), (int)floor(height / tileSize));

    for(int y = 0; y < height - tileSize; y += tileSize) {
        for(int x = 0; x < width - tileSize; x += tileSize) {
            Ground* ground = new Ground();

            ground->setX(static_cast<float>(x));
            ground->setY(static_cast<float>(y));

            _tiles.addComponent(ground);
        }
    }

    for(float i = 1; i <= 10; ++i) {
        Soldier* soldier = new Soldier();
        soldier->setX(i * 30);
        soldier->setY(i * 30);
        soldier->setTarget(soldier->getPosition());

        _selector.addSoldier(soldier);

        _tiles.addComponent(soldier);
    }
}
