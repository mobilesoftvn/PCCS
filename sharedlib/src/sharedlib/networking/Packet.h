#ifndef PACKETSTUFF_H
#define	PACKETSTUFF_H

#include <string>
#include "../CompileConfig.h"
#include <iostream>

using namespace std;



struct LIBEXPORT Packet {
public:

    static const char EOT = '>';
    static const int headerPrefixLength  = 7;
    static const int headerPostfixLength = 1;

    static bool parityCheck(char parity, Packet* packet);
    static Packet* createHeader(const char* bytes);

    // Copy ctor for pointers:
    Packet(const Packet* origin);
    Packet(void);
    Packet(short type);
    Packet(short type, string payload);
    Packet(short type, string payload, char priority);
    Packet(short type, string payload, char priority, char version);

    int length(void);

    const char* getBytes(void);
    string getPayload(void);
    void setPayload(string payload);
    short getType(void);
    int getPayloadLength(void);
    char getPriority(void);
    char getVersion(void);
    static string formatByte(char byte);
    void retain(void);
    void release(void);

private:
    void init(short type = 0, string payload = "", char priority = 0, char version = 1);

    string _payload;
    char _version;
    char _priority;
    short _type;
    int _payloadLength;
    char _headerParity;

    unsigned int _refCount;
};

#endif	/* PACKETSTUFF_H */
