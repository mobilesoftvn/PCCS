#ifndef GTSERVER_H
#define	GTSERVER_H

#include "ServerException.h"
#include <yaxl.h>
#include "../game/World.h"

class Accepter;
class Player;
class PlayerPool;

class GameHub {
public:
    GameHub();
    virtual ~GameHub();
    void onNewConnection(yaxl::socket::Socket* client);

    World world;
    
private:
    GameHub(const GameHub& orig);
    Accepter* _accepter;
    PlayerPool* _players;
};

#endif	/* GTSERVER_H */

