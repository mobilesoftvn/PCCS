#include "PacketEventMixin.h"

void PacketEventMixin::registerPacketEvent(PacketType type, PacketEvent event) {
    _packetEvents.insert(std::pair<PacketType, PacketEvent>(
        type, event
    ));
}

void PacketEventMixin::emitPacketEvent(Packet* packet) {
    const PacketType type = (PacketType) packet->getType();

    if(_packetEvents.find(type) != _packetEvents.end()) {
        PacketEvent& handler = _packetEvents[type];

        Packet* reply = handler(packet);

        if(reply != 0) {
            sendPacket(reply);
        }
    }

    delete packet;
}