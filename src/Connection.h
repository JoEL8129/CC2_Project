#ifndef CONNECTION_H
#define CONNECTION_H

#include "ofMain.h"
#include "Connector.h"

class Connector;

class Connection {
public:
    Connection(Connector* _from, Connector* _to);
    virtual ~Connection();

    void draw() const;
    bool involvesNode(Node* node) const;

private:
    Connector* from;
    Connector* to;
};

#endif

