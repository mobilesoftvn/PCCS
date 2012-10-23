#ifndef NETWORK_H
#define	NETWORK_H

#include <yaxl.h>
#include <phantom.h>
#include <sstream>
#include <PacketTypes.h>
#include "../Game.h"
#include <PacketReader.h>
#include <map>

using namespace phantom;
using namespace std;

class Reader;
class Packet;
class Ping;
class BandwidthTest;

class Network : public Composite {
public:
    Network(Game& game);
    virtual ~Network();

    void init(void);
    void addText(string text);

    void onPacketReceived(Packet* packet);
    void sendPacket(Packet* packet);

    void update(const float& elapsed);

    Ping* ping;
    BandwidthTest* bandwidthTest;

    void sendBufferedMessage(AbstractMessage* message);

    friend class Reader;
private:
    yaxl::socket::OutputStream& getOutputStream(void);
    PacketReader& getPacketReader(void);

    PacketReader* _packetReader;
    Game& _game;
    yaxl::socket::Socket* _socket;
    Reader* _reader;

    bool _isAuthenticated;

    deque<AbstractMessage*> _messages;
};

#endif	/* NETWORK_H */

