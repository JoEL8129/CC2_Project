#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "ofMain.h"
#include "Node.h"

class Node; // Forward declaration

enum class ConnectorType {
    Input,
    Output
};

class Connector {
public:
    Connector(string _name, glm::vec2 _position, ConnectorType _type, Node* _parentNode);
    virtual ~Connector();

    Node* getParentNode() const;


    void draw();
    glm::vec2 getPosition() const;
    void setPosition(const glm::vec2& _position);

    string getName() const;
    ConnectorType getType() const;

    bool isPointInside(const glm::vec2& point) const;
    void setColor(glm::vec3& _color);
    
private:
    glm::vec3 color;
    string name;
    glm::vec2 position;
    glm::vec2 size;
    ConnectorType type;
    Node* parentNode;
};

#endif
