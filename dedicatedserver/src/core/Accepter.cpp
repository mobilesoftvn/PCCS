#include "Accepter.h"

Accepter::Accepter(GameHub* server) :
    _socket(Services::settings()->dedicated_port, Services::settings()->dedicated_socketbacklog),
    _server(server)
{
    _socket.setKeepAlive(true);
}

Accepter::~Accepter() {

}

void Accepter::run(void) {
    do {
        cout << "+ Ready to accept clients." << endl;

        yaxl::socket::Socket* client = _socket.accept();

        _server->onNewConnection(client);
    } while(true);
}
