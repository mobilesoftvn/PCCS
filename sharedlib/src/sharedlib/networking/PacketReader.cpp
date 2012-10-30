#include "PacketReader.h"

PacketReader::PacketReader(yaxl::socket::InputStream& inputStream) : _inputStream(inputStream), _packet(0), _hasHeader(false) {

}

void PacketReader::readHeader() {
    const int available = _inputStream.available();

    if (available >= Packet::headerPrefixLength) {
        string bytes = _inputStream.read(Packet::headerPrefixLength);
        _packet      = Packet::createHeader(bytes.c_str());
        _hasHeader   = true;
        // TODO: parity check. Need this asap.
    }
}

Packet* PacketReader::readPayload() {
    const int readSize = _packet->getPayloadLength() + Packet::headerPostfixLength;
    int bytesLeft = readSize - _payload.length();

    // We'll permit two read tries:
    for (int i = 0; i < 2; ++i) {
        int available = _inputStream.available();

        if (available > 0) {
            int readSize = min(bytesLeft, available);
            _payload += _inputStream.read(readSize);
            bytesLeft -= readSize;
        }
    }

    if (isValid()) {
        Packet* temp = _packet;

        _payload.resize(_payload.length() - 1);
        temp->setPayload(_payload);

        reset();

        return temp;
    }

    return 0;
}

void PacketReader::reset() {
    _packet    = 0;
    _hasHeader = false;
    _payload.clear();
}

bool PacketReader::isValid() {
    if (_payload.length() - Packet::headerPostfixLength == _packet->getPayloadLength()) {
        if (_payload.length() < 1 || _payload.at(_payload.length() - 1) != Packet::EOT) {
            cout << "WARNING! Packet declined, payload is less than 1 or EOT mismatch." << endl;
            cout << "Type: " << _packet->getType() << endl;
            cout << "Prio: " << _packet->getPriority() << endl;
            cout << "Version: " << _packet->getVersion() << endl;
            cout << "Payload Size: " << _packet->getPayloadLength() << endl;

            //cout << "Dumping the first 6 bytes: " << endl;
            //for(unsigned int i = 0; i < bytes.length(); ++i) {
            //    cout << i << ": " << Packet::formatByte(bytes.at(i)) << endl;
            //}

            delete _packet;
            reset();

            return false;
        }
        return true;
    } else {
        cout << "too short read more" << endl;
    }

    return false;
}

Packet* PacketReader::readNext(void) {

    if (!_hasHeader) {
        readHeader();
    }

    if (_hasHeader) {
        return readPayload();
    }

    return 0;
}
