#ifndef NODE_H
#define NODE_H

#include "ofMain.h"
#include "Connector.h"
//#include "Connection.h"

class Connector;
//class Connection;

enum class NodeType {
    Null,
    Constant
};

class Node {
public:
    Node(string name, glm::vec2 position);
    virtual ~Node();

    void draw();
    void drawSelected();

    virtual void setupParameters(); // Setup parameters for the node
    ofParameterGroup& getParameters() { return parameters; } // Access parameters

    void setPosition(const glm::vec2& position);
    void setScale(float scale);

    glm::vec2 getPosition() const;
    Connector* getConnectorAt(const glm::vec2& point);
    vector<Connector> getInputConnectors();
    vector<Connector> getOutputConnectors();


    string getName() const;
    NodeType getType() const;

    void addInputConnector(string name, glm::vec2 position);
    void addOutputConnector(string name, glm::vec2 position);

    //bool connectTo(Node* targetNode, const string& outputName, const string& inputName);
    bool isMouseInside(const glm::vec2& mousePosition, float scaleFactor);

protected:
    string name;
    NodeType type;

    glm::vec2 position;
    glm::vec2 size;
    glm::vec2 selSizeOffset;
    float scaleFactor;

    vector<Connector> inputConnectors;
    vector<Connector> outputConnectors;
    //vector<Connection> connections;

    ofParameterGroup parameters;


};

/*class NullNode : public Node {
public:
    NullNode(string name, glm::vec2 position);
};*/



#endif