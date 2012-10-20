#ifndef READER_H
#define	READER_H

#include <yaxl.h>
#include <phantom.h>
#include "Network.h"
#include <Packet.h>
#include <sstream>

using namespace phantom;
using namespace std;

class Reader : public yaxl::concurrency::Thread {
public:
    Reader(Network& network);
    virtual ~Reader();
    virtual void run(void);

private:
    Network& _network;
};

#endif	/* READER_H */

