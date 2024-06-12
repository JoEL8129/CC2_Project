#ifndef NODE_H
#define NODE_H

#include "ofMain.h"
#include "Connector.h"
#include "Connection.h"

class Connector;
class Connection;


class Node {
public:
    Node(string name, glm::vec2 position);
    virtual ~Node();

    void draw();
    void drawSelected();

    void setPosition(const glm::vec2& position);
    glm::vec2 getPosition() const;
    void setScale(float scale);

    string getName() const;
    
    void addInputConnector(string name, glm::vec2 position);
    void addOutputConnector(string name, glm::vec2 position);

    bool connectTo(Node* targetNode, const string& outputName, const string& inputName);
    
    Connector* getConnectorAt(const glm::vec2& point);
    vector<Connector> getInputConnectors();
    vector<Connector> getOutputConnectors();

protected:
    string name;
    glm::vec2 position;
    glm::vec2 size;
    glm::vec2 selSizeOffset;
    float scaleFactor;

    vector<Connector> inputConnectors;
    vector<Connector> outputConnectors;
    vector<Connection> connections;


};

class NullNode : public Node {
public:
    NullNode(string name, glm::vec2 position);
};



#endif