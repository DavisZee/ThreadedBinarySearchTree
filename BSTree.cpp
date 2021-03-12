/*
 * Created on 02/26/2021
 * Modified by Davis Zhong on 02/26/2021
 * Modified by Affan Dhankwala on 3/3/2021
*/

#include <cassert>
#include <iostream>
#include <string>

#include "BSTree.h"

using namespace std;

ostream& operator<<(ostream& out, const BSTree& tree) {
    //out << tree.toStringTree();
	return out;
}

// LeafNode Public:

// constructor
LeafNode::LeafNode() : leftChild{ nullptr }, rightChild{ nullptr }, lThread{ false }, 
rThread{ false }
{}

// constructor with data input
LeafNode::LeafNode(const int& newData) : data{newData}, leftChild{nullptr}, 
    rightChild{nullptr}, lThread{ false }, rThread{ false }
{}

//constructure with all variables argument
LeafNode::LeafNode(const int& newData, LeafNode* leftPtr, LeafNode* rightPtr) : 
    data{newData}, leftChild{leftPtr}, rightChild{rightPtr}, lThread{ false }, rThread{ false }
{}


void LeafNode::setData(const int& newData) {
    data = newData;
}

int LeafNode::getData() {
    return data;
}

bool LeafNode::isLeafNode() const {
    return (leafState == true);
}

auto LeafNode::getLeftChildPtr() const {
    return leftChild;
}

auto LeafNode::getRightChildPtr() const {
    return rightChild;
}

void LeafNode::setLeftChild(LeafNode* leftLeaf) {
    leftChild = leftLeaf;
}

void LeafNode::setRightChild(LeafNode* rightLeaf) {
    rightChild = rightLeaf;
}

//BSTree protected
// goes through the tree and returns the height of the longest branch
int BSTree::getHeightHelper(LeafNode* subTreePtr) const {
    if (subTreePtr == rootPtr) return 0;
    
    int leftHeight = getHeightHelper(subTreePtr->leftChild);
    int rightHeight = getHeightHelper(subTreePtr->rightChild);


    //returns the max of leftHeight and rightHeight (+ 1 to account for itself)
    return (leftHeight < rightHeight) ? rightHeight + 1: leftHeight + 1;
}
// toString all levels
string BSTree::toStringTree() {
    string s = nullptr;
    int height = getHeightHelper(rootPtr);
    for (int i = 0; i < height; i++) {
        s += toStringGivenLevel(rootPtr, i);
        s += "\n";
    }
}
// toString given a level
string BSTree::toStringGivenLevel(LeafNode* root, int level) {
    string oneLevel = nullptr;
    if (root == rootPtr) return oneLevel;
    if (level = 1) {
        oneLevel += root->getData();
    }else if (level > 1) {
        toStringGivenLevel(root->leftChild, level - 1);
        toStringGivenLevel(root->rightChild, level - 1);
    }
    return oneLevel;
}

int BSTree::getNumOfNodesHelper(LeafNode* subTreePtr) const {
    if (subTreePtr == nullptr) return 0;
    int counter = 0;
    //Recursively traverse tree going left then right if have those children
    
    counter += getNumOfNodesHelper(subTreePtr->leftChild);
    counter += getNumOfNodesHelper(subTreePtr->rightChild);
  
    //Return the count (+1 to account for itself)
    return counter + 1;
}



bool BSTree::removeValue(LeafNode* subTreePtr, const int target) {
    // careful of mem leak
	return true;
}

auto BSTree::moveValuesUpTree(LeafNode* subTreePtr) {
	return;
}

LeafNode* BSTree::findNode(LeafNode* treePtr, const int target) const {
    if (treePtr->data == target) return treePtr;
    //If there is nowhere to go then we have hit the bottom and have not found node.
    else if (treePtr->rThread == false && treePtr->lThread == false) return nullptr;

    else if (treePtr->data > target) return findNode(treePtr->leftChild, target);

    else if (treePtr->data < target) return findNode(treePtr->rightChild, target);

    //At this point, target was not in the tree and thus return null ptr
    return nullptr;
}

LeafNode* BSTree::copyTree(LeafNode* oldTreeRootPtr) {
    if (oldTreeRootPtr == nullptr) return nullptr;
    LeafNode* temp = new LeafNode();
    temp = oldTreeRootPtr;
    
    temp->leftChild = copyTree(oldTreeRootPtr->leftChild);
    temp->rightChild = copyTree(oldTreeRootPtr->rightChild);
    // clean up 
    temp = nullptr;
    delete temp;
    return oldTreeRootPtr;
}

//destroys all nodes in the tree and makes sure there is no mem leak
void BSTree::burnTheTree(LeafNode* subTreePtr) {

}

void BSTree::preorder(void visit(int), LeafNode* treePtr) {

}

void BSTree::inorder(void visit(int), LeafNode* treePtr) {

}

void BSTree::postorder(void visit(int), LeafNode* treePtr) {

}

//BSTree public

BSTree::BSTree() {
    //In the case of empty, root will be a dummy node
    rootPtr = new LeafNode();
}

BSTree::BSTree(const int data) {
   //This method will add all values from 1 - data into BSTree

    //Dummy node
    rootPtr = new LeafNode();
    //Link whole tree to be on left of dummy node
    rootPtr->rThread = true;
    rootPtr->lThread = false;
    rootPtr->leftChild = rootPtr;
    rootPtr->rightChild = rootPtr;
    //Call BalancedAdd to add all values into tree in correct order
    balancedAdd(1, data);
    
}

void BSTree::balancedAdd(int start, int end) {
    // maybe check and set leafState in this metho
    if (start > end) return;

    int mid = (start + end) / 2;

    add(mid);

    balancedAdd(start, mid - 1);

    balancedAdd( mid + 1, end);

}

LeafNode* BSTree::sortedArrToTree(int arr[], int start, int end) {

    if (start > end) return NULL;

    int mid = (start + end) / 2;

    //Assign root as middle pointer
    LeafNode* midNode = new LeafNode(arr[mid - 1]);


    //Recursively link left and right sides
    midNode->leftChild = sortedArrToTree(arr, start, mid - 1);

    //Recursively link right side
    midNode->rightChild = sortedArrToTree(arr, mid + 1, end);   

    return midNode;
}

BSTree::BSTree(const int data, BSTree* leftTreePtr, BSTree* rightTreePtr) {
    rootPtr->data = data;
    rootPtr->leftChild = copyTree(leftTreePtr->rootPtr);
    rootPtr->rightChild = copyTree(rightTreePtr->rootPtr);
}

BSTree::BSTree(const BSTree* aTree) {
    
    rootPtr = copyTree(aTree->rootPtr);

}

BSTree::~BSTree() {
    LeafNode* del;
    LeafNode* trav = rootPtr->leftChild;
    // traverse tree
    // delete nodes individually 
    // until I hit the left most leaf keep looping
    while (!trav->lThread) {
        trav = trav->leftChild;        
    }
    // while the right thread isnt false keep looping
    while (trav->rightChild == nullptr) {
        del = trav;
        trav = trav->rightChild;
        delete del;
    }
}


//
bool BSTree::isEmpty() const {
	return rootPtr == nullptr; // if root is nullptr then tree is empty
}

int BSTree::getHeight() const {
    return getHeightHelper(rootPtr);
}

int BSTree::getNumOfNodes() const {
    return getNumOfNodesHelper(rootPtr);
}

int BSTree::getRootData() const {
    //Compensate for dummy node
	return rootPtr->leftChild->data;
}

void BSTree::setRootData(const int newData) {
    //Compensate for dummy node
    rootPtr->leftChild->data = newData;
}

bool BSTree::add(const int newData) {
    //first check if tree is empty
    if ((rootPtr->leftChild == rootPtr) && (rootPtr->rightChild == rootPtr)) {
        //At this point the tree is empty and only has dummy node
        LeafNode* tempNode = new LeafNode();
        //Reroute all pointers of root to tempNode
        tempNode->data = newData;
        tempNode->leftChild = rootPtr->leftChild;
        tempNode->lThread = rootPtr->lThread;
        tempNode->rThread = false;
        tempNode->rightChild = rootPtr->rightChild;
        //Insert tempNode into tree
        rootPtr->leftChild = tempNode;
        rootPtr->lThread = true;
        // clean up tempNode
        tempNode = nullptr;
        delete tempNode;
        return true;
    }
    //Tree is not empty so we will have to just add it
    LeafNode* ptr = new LeafNode();
    //This will avoid the dummy node
    ptr = rootPtr->leftChild;
    //Keep looping until internally stopped by return
    while (true) {
        if (newData == ptr->data) return false; 
        //Do same thing if it is larger than the current node data
        if (newData > ptr->data) {
            LeafNode* tempNode = new LeafNode(newData);
            if (ptr->rThread == false) {
                tempNode->rightChild = ptr->rightChild;
                tempNode->rThread = ptr->rThread;
                tempNode->lThread = false;
                tempNode->leftChild = ptr;

                ptr->rThread = true;
                ptr->rightChild = tempNode;
                return true;
            }
            else ptr = ptr->rightChild;
        }
        
        if (newData < ptr->data) {
            //In this case, we need to navigate left
            LeafNode* tempNode = new LeafNode(newData);
            if (ptr->lThread == false) {
                // At this point we know that the leftChild does not 
                // point to any inorder predecessor. 
                tempNode->leftChild = ptr->leftChild;
                tempNode->lThread = ptr->lThread;
                tempNode->rThread = false;

                //Point to inorder successor 
                tempNode->rightChild = ptr;
                ptr->lThread = true;
                ptr->leftChild = tempNode;
                return true;
            }
            else ptr = ptr->leftChild;

        }
    }
}

bool BSTree::remove(const int data) {
    //Set parent to dummy node and our pointer to the real root
    LeafNode* parent = rootPtr, *ptr = rootPtr->leftChild;
    bool found = false;
    //Can use findNode function but we won't get the parent node (need that for linking)
    //Traverse tree until find target node and remember parent
    while (ptr != nullptr) {
        if (data == ptr->data) {
            found = true;   //We found the node
            break;
        }
        parent = ptr;
        if (data < ptr->data){
            if (ptr->lThread == true) {
                ptr = ptr->leftChild;
            }
            else break;
        }
        else {
            if (ptr->rThread == true) {
                ptr = ptr->rightChild;
            }
            else break;
        }
    }
    if (!found) return false;
    
    //At this point we have the target node and we have its parent as well

    //Now we have to remove and link the new nodes depending on their children

    //If ptr has two children, then both threads will be true and we would need to
    //reroute the pointers for both children
    if (ptr->rThread && ptr->lThread) {
        deleteTwoChild(ptr, parent);
    }
    //If ptr only has one child
    else if (ptr->rThread && !(ptr->lThread)||(!(ptr->rThread) && (ptr->lThread))) {
        deleteOneChild(ptr, parent);
    }
 
    //If ptr has no children (is a leaf)
    else {
        deleteNoChild(ptr, parent);
    }
    
	return true;
}

//If target has no children there, only need to reroute parent pointers
void BSTree::deleteNoChild(LeafNode* ptr, LeafNode* parent) {
    if (ptr == parent->leftChild) {
        //Now the left thread of parent is a thread
        parent->lThread = false;
        parent->leftChild = ptr->leftChild;
    }
    else {
        parent->rThread = false;
        parent->rightChild = ptr->rightChild;
    }
    delete ptr;
}

void BSTree::deleteOneChild(LeafNode* ptr, LeafNode* parent) {
    LeafNode* child = new LeafNode();
    //Find out whether ptr has right or left child
    if (ptr->lThread) {
        child = ptr->leftChild;
    }
    else {
        child = ptr->rightChild;
    }
    
    if (ptr == parent->leftChild) {
        parent->leftChild = child;
    }
    else parent->rightChild = child;

    LeafNode* successor = inorderSuccessor(ptr);
    LeafNode* predecessor = inorderPredecessor(ptr);
    
    if (!ptr->lThread) {
        predecessor->rightChild = successor;
    }
    else if (!ptr->rThread) successor->leftChild = predecessor;
    
    delete ptr;
}

void BSTree::deleteTwoChild(LeafNode* ptr, LeafNode* parent) {
    LeafNode* successor = ptr->rightChild;
    LeafNode* parentSuccessor = ptr;

    while (successor->lThread) {
        parentSuccessor = successor;
        successor = successor->leftChild;

    }
    parentSuccessor->data = successor->data;
    
    if ((!successor->lThread) && !(successor->rThread)) deleteNoChild(successor, parentSuccessor);

    else deleteOneChild(successor, parentSuccessor);
}
void BSTree::clear() {
    
}

LeafNode* BSTree::inorderSuccessor(LeafNode* ptr) {
    //If there is a thread then return the next threaded node
    if (!ptr->rThread) {
        return ptr->rightChild;
    }
    //If no thread then inorder successor is the leftmost node of node to right
    ptr = ptr->rightChild;
    while (ptr->lThread) {
        ptr = ptr->leftChild;
    }
    return ptr;
}

LeafNode* BSTree::inorderPredecessor(LeafNode* ptr) {
    if (!ptr->lThread) {
        return ptr->leftChild;
    }
    ptr = ptr->leftChild;
    while (ptr->rThread) {
        ptr = ptr->rightChild;
    }
    return ptr;
}

int BSTree::getEntry(const int anEntry) {
	return 0;
	
}

bool BSTree::contains(const int anEntry) const {
    //Return true if findNode returns a ptr and false if returns nullptr
    return (findNode(rootPtr->leftChild, anEntry) != nullptr) ? true : false;
}

void BSTree::preorderTrav(void visit(int&)) const {

}

string BSTree::inorderTrav() {    
    LeafNode* ptr = rootPtr->leftChild;
    //Go to most left node
    while (ptr->lThread) {
        ptr = ptr->leftChild;
    }
    //At this point we are at the right-most node
    string traversal = "";
    //Continue right until we loop back to the dummy node
    while (ptr != rootPtr) {
        traversal += to_string(ptr->data) + " ";
        ptr = inorderSuccessor(ptr);
    }
    return traversal;
}

void BSTree::postorderTrav(void visit(int&)) const {

}

BSTree& BSTree::operator= (const BSTree& rightHandSIde) {
    return *this;
}
