#include "ofApp.h"

void ofApp::setup() {
    gui.setup();
    inspectorPanel.setup("Inspector","abs",ofGetWidth() - 250, 20);
    //nodeCreationPanel.setup();
   
    gui.add(addButton.setup("Add Node"));
    gui.add(deleteButton.setup("Delete Node"));
    gui.add(connectButton.setup("Connect Nodes"));
    

    addButton.addListener(this, &ofApp::addButtonPressed);
    deleteButton.addListener(this, &ofApp::deleteButtonPressed);
    connectButton.addListener(this, &ofApp::connectButtonPressed);

    ExistingNodeTypes = {NodeType::Null,NodeType::Constant};

    //createNodeCreationButtons();


    selectedNode = nullptr;
    dragging = false;
    scrolling = false;  
    isConnecting = false;
    isNodeCreationPanelVisible = false;

    scaleFactor = 1.0f;
    debugValue = 0;

}

void ofApp::update() {

 


}

void ofApp::draw() {
        

    ofDrawBitmapString("value: " + ofToString(debugValue), ofGetWidth()-150, 10);


    ofPushMatrix();
    ofScale(scaleFactor, scaleFactor);  // Apply scaling

    if (isConnecting) {
        ofSetColor(255, 0, 255);  // Set color for the connection line
        ofDrawLine(connectionStart, glm::vec2(ofGetMouseX() / scaleFactor, ofGetMouseY() / scaleFactor));
    }

    if (selectedNode != nullptr) {
        selectedNode->drawSelected();
    }
    
   for (auto& node : nodes) {
       node->draw();    
   }

   for (auto& connection : connections) {
       connection->draw();
   }

   ofPopMatrix();

    //gui.draw();
    inspectorPanel.draw();
    if (isNodeCreationPanelVisible) {
        nodeCreationPanel.draw();
    }
}

void ofApp::keyPressed(int key) {
    if (key == OF_KEY_DEL && selectedNode || key== OF_KEY_BACKSPACE && selectedNode) {

        deleteNode(selectedNode);

        /*auto it = std::find(nodes.begin(), nodes.end(), selectedNode);
        if (it != nodes.end()) {
            delete* it;
            nodes.erase(it);
            selectedNode = nullptr;
            updateInspector();
        }*/
    } else if (key == 'f' || key == 'F') {
        frameAllNodes();
    }
    else if (key == OF_KEY_TAB) {
        nodeCreationPanel.setup("afaf","bfaf",ofGetMouseX(), ofGetMouseY());
        createNodeCreationButtons();

        isNodeCreationPanelVisible = !isNodeCreationPanelVisible;
    }

}

void ofApp::mousePressed(int x, int y, int button) {
    glm::vec2 mousePos(x, y);
    if (button == OF_MOUSE_BUTTON_MIDDLE) {  // Middle mouse button
        scrolling = true;  // Start scrolling
        prevMousePos = glm::vec2(x, y);
    } else {
        for (auto& node : nodes) {

            Connector* connector = node->getConnectorAt(mousePos/scaleFactor);
            if (connector) {
                isConnecting = true;
                connector->setColor(glm::vec3(255, 0, 255));
                connectionStart = connector->getPosition();
                draggedConnector = connector;
                dragStart = connector->getPosition();
                break;
            }


            //if (ofRectangle(node->getPosition(), 100, 50).inside(x / scaleFactor, y / scaleFactor))


            glm::vec2 clickOffset = glm::vec2(x / scaleFactor, y / scaleFactor) - node->getPosition();

            if (node->isMouseInside(mousePos, scaleFactor)) {
                selectedNode = node;
                updateInspector();
                dragging = true;
                selectedNodeOffset = clickOffset;
                break;
            }

            if (isNodeCreationPanelVisible && ofRectangle(nodeCreationPanel.getPosition(),nodeCreationPanel.getWidth(),nodeCreationPanel.getHeight()).inside(x,y)==false ) {
                isNodeCreationPanelVisible = false;
            }
        }
    }

}

void ofApp::mouseReleased(int x, int y, int button) {
    

    if (button == OF_MOUSE_BUTTON_MIDDLE) {  // Middle mouse button
        scrolling = false;  // Stop scrolling
    }
    else {
        dragging = false;

    }

    if (draggedConnector) {
        glm::vec2 mousePos(x, y);
        tryCreateConnection(mousePos);
        draggedConnector = nullptr;
        isConnecting = false;
    }
  
}

void ofApp::mouseDragged(int x, int y, int button) {



    if (dragging && selectedNode) {
        selectedNode->setPosition(glm::vec2(x / scaleFactor, y / scaleFactor) - selectedNodeOffset);
    }

    if (scrolling) {
        glm::vec2 currentMousePos(x, y);
        glm::vec2 diff = currentMousePos - prevMousePos;

        // Adjust for scaling
        diff /= scaleFactor;

        // Update node positions
        for (auto& node : nodes) {
            node->setPosition(node->getPosition() + diff);
        }

        prevMousePos = currentMousePos;
    }
}

void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY) {
    float zoomSpeed = 0.02f;
    if (scrollY > 0) {
        scaleFactor += zoomSpeed;  // Zoom in
    }
    else if (scrollY < 0) {
        scaleFactor -= zoomSpeed;  // Zoom out
    }

    scaleFactor = ofClamp(scaleFactor, 0.3f, 5.0f);  // Clamp the scale factor to avoid negative or too large values
}

void ofApp::frameAllNodes() {
    // Calculate centroid of all nodes
    glm::vec2 centroid(0, 0);
    for (auto& node : nodes) {
        centroid += node->getPosition();
    }
    centroid /= nodes.size();

    // Calculate the bounding box of all nodes
    glm::vec2 minPos(FLT_MAX, FLT_MAX);
    glm::vec2 maxPos(-FLT_MAX, -FLT_MAX);
    for (auto& node : nodes) {
        glm::vec2 pos = node->getPosition();
        minPos.x = std::min(minPos.x, pos.x);
        minPos.y = std::min(minPos.y, pos.y);
        maxPos.x = std::max(maxPos.x, pos.x);
        maxPos.y = std::max(maxPos.y, pos.y);
    }

    // Calculate the required scale factor to fit all nodes within 80% of the window size
    float windowWidth = ofGetWidth() * 0.8f;
    float windowHeight = ofGetHeight() * 0.8f;
    float scaleFactorToFitWidth = windowWidth / (maxPos.x - minPos.x);
    float scaleFactorToFitHeight = windowHeight / (maxPos.y - minPos.y);
    float scaleFactorToFit = std::min(scaleFactorToFitWidth, scaleFactorToFitHeight);

    // Calculate the translation needed to center the centroid
    glm::vec2 translation = glm::vec2(ofGetWidth() / 2, ofGetHeight() / 2) - centroid * scaleFactorToFit;

    // Apply the translation and scale factor to all nodes
    for (auto& node : nodes) {
        glm::vec2 newPos = (node->getPosition() * scaleFactorToFit) + translation;
        node->setPosition(newPos);
        node->setScale(scaleFactorToFit);
    }

    // Update the global scale factor
    scaleFactor = scaleFactorToFit;
}

void ofApp::createNode(const NodeType& _type) {
    if (_type == NodeType::Null) {
        nodes.push_back(new Node_Null("Null" + ofToString(nodes.size()), glm::vec2(ofGetMouseX(), ofGetMouseY())));
    }
    else if (_type == NodeType::Constant) {
        nodes.push_back(new Node_Constant("Constant" + ofToString(nodes.size()), glm::vec2(ofGetMouseX(), ofGetMouseY())));

    }
}

void ofApp::deleteNode(Node* _node) {

    // Style 1 
    /*
    connections.erase(
        std::remove_if(connections.begin(), connections.end(),
            [_node](const Connection* connection) {
                return connection->involvesNode(_node);
            }),
        connections.end()
                );
    */
    // Style 2
    // Remove and delete all connections involving this node
    for (auto it = connections.begin(); it != connections.end();) {
        if ((*it)->involvesNode(_node)) { //using '(*it)' instead of only '*it' because the arrow operator is computed before dereference operator, so '*it' would give wrong result 
            delete* it; // Delete the connection object
            it = connections.erase(it); // Erase the pointer from the vector
        }
        else {
            ++it;
        }
    }

    auto it = std::find(nodes.begin(), nodes.end(), _node);
    if (it != nodes.end()) {
        delete* it;
        nodes.erase(it);
    }

    if (selectedNode == _node) {
        selectedNode = nullptr;
        updateInspector();
    }
    
    

}


void ofApp::updateInspector() {
    inspectorPanel.clear(); // Clear existing GUI
    inspectorPanel.setup("Inspector", "abs", ofGetWidth() - 250, 20);

    if (selectedNode) {
        inspectorPanel.add(selectedNode->getParameters()); // Add parameters of the selected node
    }
}

// Starter GUI 
void ofApp::addButtonPressed() {
    createNode(NodeType::Constant);
    //nodes.push_back(new Node_Null("NullNode", glm::vec2(ofGetWidth() / 2, ofGetHeight() / 2)));
}

void ofApp::deleteButtonPressed() {

}

void ofApp::connectButtonPressed() {
    // Placeholder for connection logic
}

void ofApp::tryCreateConnection(const glm::vec2& mousePos) {
    for (auto* node : nodes) {
        Connector* targetConnector = node->getConnectorAt(mousePos/scaleFactor);
        if (targetConnector && targetConnector != draggedConnector &&
            draggedConnector->getType() != targetConnector->getType() && 
            targetConnector->getType() != ConnectorType::Output
            ) {
            debugValue += 5;              
            connections.push_back(new Connection(targetConnector, draggedConnector));
        }
    }
}

void ofApp::createNodeCreationButtons() {
    // Create buttons for each NodeType
    for (const auto& type : ExistingNodeTypes) {
        ofxButton* button = new ofxButton();

        std::string buttonName;
        switch (type) {
        case NodeType::Null: buttonName = "Create Null Node"; break;
        case NodeType::Constant: buttonName = "Create Constant Node"; break;
        }

        nodeCreationPanel.add(button->setup(buttonName));

        switch (type) {
        case NodeType::Null:
            button ->addListener( this, &ofApp::createNullNode);
            break;
        case NodeType::Constant:
            button->addListener(this, &ofApp::createConstantNode);
            break;
        }

        nodeCreationButtons.push_back(button);
    }
}

void ofApp::createNullNode() {
    createNode(NodeType::Null);
    isNodeCreationPanelVisible = false;
}

void ofApp::createConstantNode() {
    createNode(NodeType::Constant);
    isNodeCreationPanelVisible = false;
}