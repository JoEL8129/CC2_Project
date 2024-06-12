#ifndef NODE_NULL_H
#define NODE_NULL_H

#include "Node.h"

class Node_Null : public Node {
public:
    Node_Null(string name, glm::vec2 position);
    void setupParameters() override; // Override to setup specific parameters
};

#endif