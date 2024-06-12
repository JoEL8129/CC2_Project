#include "Connector.h"

Connector::Connector(string _name, glm::vec2 _position, ConnectorType _type, Node* _parentNode)
    : name(_name), position(_position), type(_type), size(5, 5), color(255,0,0), parentNode(_parentNode) {
}

Connector::~Connector() {
}

void Connector::draw() {
    ofSetColor(color.x,color.y,color.z);
    ofDrawCircle(position, size.x);
}

glm::vec2 Connector::getPosition() const {
    return position;
}

void Connector::setPosition(const glm::vec2& _position) {
    this->position = _position;
}

string Connector::getName() const {
    return name;
}

ConnectorType Connector::getType() const {
    return type;
}

Node* Connector::getParentNode() const {
    return parentNode;
}

void Connector::setColor(glm::vec3& _color) {
    color = _color;
}

bool Connector::isPointInside(const glm::vec2& point) const {
    return glm::distance(point, position) <= size.x;
}
