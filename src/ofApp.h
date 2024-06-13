#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Node.h"
#include "Node_Null.h"
#include "Connection.h"

//class Connection;

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    void mouseDragged(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseScrolled(int x, int y, float scrollX, float scrollY);

    
    
    void createNode(const string& nodeName);
    void deleteNode(Node* _node);

    void nodeSelected(Node* selectedNode);


private:

    void addButtonPressed();   // Add this declaration
    void deleteButtonPressed(); // Add this declaration
    void connectButtonPressed(); // Add this declaration

    vector<Node*> nodes;
    vector<Connection*> connections;


    ofxPanel gui;
    ofxPanel inspectorPanel;

    ofxButton addButton;
    ofxButton deleteButton;
    ofxButton connectButton;

    int debugValue;

    float scaleFactor;

    void frameAllNodes();
    
    Node* selectedNode;

    // Flags
    bool dragging;
    bool scrolling;  // Flag to indicate scrolling
    bool isConnecting;  // Flag to indicate if a connection is being dragged

    glm::vec2 prevMousePos;  // Previous mouse position for scrolling
    glm::vec2 selectedNodeOffset;

    // Connector Stuff
    Connector* draggedConnector;
    glm::vec2 dragStart;
    glm::vec2 connectionStart;  // Store the start position of the connection
    void tryCreateConnection(const glm::vec2& mousePos);

    void updateInspector();
};
