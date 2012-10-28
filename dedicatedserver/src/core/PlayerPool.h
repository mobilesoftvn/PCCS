#ifndef PLAYERPOOL_H
#define	PLAYERPOOL_H

#include <deque>
#include <iostream>
#include <string>
#include <yaxl.h>
#include <sharedlib/models/PlayerModel.h>
#include <sharedlib/networking/Packet.h>

class Player;
class GameHub;

class PlayerPool : public yaxl::concurrency::Thread {
public:
    PlayerPool(GameHub* gamehub);
    ~PlayerPool();
    void addPlayer(Player* player);

    PlayerModel createPlayerModel(void);

    void broadcast(Packet* packet, const PlayerModel& exclude);
    void broadcast(Packet* packet);

    void run(void);
private:
    deque<Player*> _players;
    GameHub* _gamehub;
    yaxl::concurrency::Mutex _playersMutex;

    int _playerUID;
};

#endif	/* PLAYERPOOL_H */

