#ifndef CONNECTION_H
#define CONNECTION_H

#include "ofMain.h"
#include "Connector.h"

class Connector;

class Connection {
public:
    Connection(Connector* output, Connector* input);
    virtual ~Connection();

    void draw();

private:
    Connector* outputConnector;
    Connector* inputConnector;
};

#endif

