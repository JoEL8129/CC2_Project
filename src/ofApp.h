#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Node.h"

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

    void frameAllNodes();
    

private:

    void addButtonPressed();   // Add this declaration
    void deleteButtonPressed(); // Add this declaration
    void connectButtonPressed(); // Add this declaration

    vector<Node*> nodes;

    ofxPanel gui;
    ofxButton addButton;
    ofxButton deleteButton;
    ofxButton connectButton;

    int debugValue;




    void createNode(const string& nodeName);



    //void updateAutocompleteSuggestions();
    //void createNode(const std::string& nodeType);


    Node* selectedNode;
    bool dragging;
    bool scrolling;  // Flag to indicate scrolling
    bool isConnecting;  // Flag to indicate if a connection is being dragged

    glm::vec2 prevMousePos;  // Previous mouse position for scrolling
    glm::vec2 connectionStart;  // Store the start position of the connection


    float scaleFactor;
    glm::vec2 selectedNodeOffset;


    Connector* draggedConnector;
    glm::vec2 dragStart;

    void tryCreateConnection(const glm::vec2& mousePos);
    
};
