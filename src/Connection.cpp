#include "Connection.h"

Connection::Connection(Connector* output, Connector* input)
    : outputConnector(output), inputConnector(input) {
}

Connection::~Connection() {
}

void Connection::draw() {
    if (outputConnector && inputConnector) {
        ofSetColor(0, 255, 0);
        ofDrawLine(outputConnector->getPosition(), inputConnector->getPosition());
    }
}
