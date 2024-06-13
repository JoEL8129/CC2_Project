#include "Connection.h"

Connection::Connection(Connector* _from, Connector* _to)
    : from(_from), to(_to) {
}

Connection::~Connection() {
}

void Connection::draw() const {
    if (from && to) {
        ofSetColor(0, 255, 0);
        ofDrawLine(from->getPosition(), to->getPosition());
    }
}

bool Connection::involvesNode(Node* node) const {
    return from->getParentNode() == node || to->getParentNode() == node;
}
