#ifndef NODE_CONSTANT_H
#define NODE_CONSTANT_H

#include "Node.h"

class Node_Constant : public Node {
public:
    Node_Constant(string name, glm::vec2 position);
    void setupParameters() override; // Override to setup specific parameters
};

#endif