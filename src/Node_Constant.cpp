#include "Node_Constant.h"

Node_Constant::Node_Constant(string name, glm::vec2 position)
    : Node(name, position) {
    type = NodeType::Constant;
    //addInputConnector("Input 1", glm::vec2(0 + position.x, 25 + position.y));
    addOutputConnector("Output 1", glm::vec2(100 + position.x, 25 + position.y));
    setupParameters();
}

void Node_Constant::setupParameters() {
    parameters.setName(name);
    ofParameter<int> Integer;
    Integer.set("Integer", 0, 0, 100);
    parameters.add(Integer);
}
