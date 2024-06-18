#include "Node_Null.h"

Node_Null::Node_Null(string name, glm::vec2 position)
    : Node(name, position) {
    type = NodeType::Null;
    addInputConnector("Input 1", glm::vec2(0 + position.x, 25 + position.y));
    addOutputConnector("Output 1", glm::vec2(100 + position.x, 25 + position.y));
    setupParameters();
}

void Node_Null::setupParameters() {
    parameters.setName(name);
    ofParameter<int> testValue;
    testValue.set("Test Value", 0, 0, 100);
    parameters.add(testValue);
} 
