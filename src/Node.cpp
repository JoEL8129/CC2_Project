#include "Node.h"

Node::Node(string _name, glm::vec2 _position)
    : name(_name), position(_position), size(100,50),selSizeOffset(12,10), scaleFactor(1.0f){
    setupParameters(); // Setup parameters in constructor
}

Node::~Node() {
}

void Node::setupParameters() {
}

void Node::draw() {

    ofSetColor(150);
    ofDrawRectRounded(position.x, position.y, size.x, size.y, 5);
    ofSetColor(0);
    ofDrawBitmapString(name, position.x+10, position.y+25);

    for (auto& connector : inputConnectors) {
        connector.draw();
    }
    for (auto& connector : outputConnectors) {
        connector.draw();
    }

}

void Node::drawSelected() {
    ofSetColor(0, 0, 175);
    ofDrawRectRounded(position.x - selSizeOffset.x / 2, position.y - selSizeOffset.y / 2, size.x + selSizeOffset.x, size.y + selSizeOffset.y, 6);
}


void Node::addInputConnector(string name, glm::vec2 position) {
    inputConnectors.emplace_back(name, position, ConnectorType::Input,this);
}

void Node::addOutputConnector(string name, glm::vec2 position) {
    outputConnectors.emplace_back(name, position, ConnectorType::Output,this);
}

void Node::setPosition(const glm::vec2& position) {
    

    glm::vec2 positionChange = position - this->position; // Calculate the change in position

// Update the position of the node
    this->position = position;

    // Update the positions of all connectors
    for (auto& connector : inputConnectors) {
        connector.setPosition(connector.getPosition() + positionChange);
    }

    for (auto& connector : outputConnectors) {
        connector.setPosition(connector.getPosition() + positionChange);
    }
}

glm::vec2 Node::getPosition() const {
    return position;
}

void Node::setScale(float scale) {
    this->scaleFactor = scale;
}

string Node::getName() const {
    return name;
}

/*bool Node::connectTo(Node* targetNode, const string& outputName, const string& inputName) {
    Connector* outputConnector = nullptr;
    Connector* inputConnector = nullptr;

    // Find the output connector by name
    for (auto& connector : outputConnectors) {
        if (connector.getName() == outputName) {
            outputConnector = &connector;
            break;
        }
    }

    // Find the input connector by name
    for (auto& connector : targetNode->inputConnectors) {
        if (connector.getName() == inputName) {
            inputConnector = &connector;
            break;
        }
    }

    if (outputConnector && inputConnector) {
        connections.emplace_back(outputConnector, inputConnector);
        return true;
    }

    return false;
}
*/

bool Node::isMouseInside(const glm::vec2& mousePosition, float scaleFactor) {
    return ofRectangle(position, size.x, size.y).inside(mousePosition.x / scaleFactor, mousePosition.y / scaleFactor);
}

Connector* Node::getConnectorAt(const glm::vec2& point) {
    for (auto& connector : inputConnectors) {
        if (connector.isPointInside(point)) {
            return &connector;
        }
    }
    for (auto& connector : outputConnectors) {
        if (connector.isPointInside(point)) {
            return &connector;
        }
    }
    return nullptr;
}

vector<Connector> Node::getInputConnectors(){
    return inputConnectors;
}

vector<Connector> Node::getOutputConnectors() {
    return outputConnectors;
}

/*NullNode::NullNode(string name, glm::vec2 position)
    : Node(name, position) {

    addInputConnector("Input 1", glm::vec2(0+position.x, 25 + position.y));
    addOutputConnector("Output 1", glm::vec2(100 + position.x, 25 + position.y));
}*/
