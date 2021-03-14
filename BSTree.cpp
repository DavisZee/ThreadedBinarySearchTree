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


// Purpose: << Operator overload of BSTree class.
// Preconditon: Arguments ostream and BSTree are  not null.
// Postcondition: String stream of tree is successfully returned.
ostream& operator<<(ostream& out, const BSTree& tree) {
    BSTree newTree(tree);
    out << newTree.inorderTrav();
	return out;
} // end of << op overload

/*
ostream& operator<<(ostream& out, const BSTree& tree) {
    BSTree newTree(tree);
    int height = newTree.getHeightHelper(newTree.rootPtr->leftChild);
    cout << "height " << height << endl;
    string strOut = "";
    for (int i = 1; i <= height; i++) {
        newTree.toStringGivenLevel(newTree.rootPtr->leftChild, i, strOut);
        cout << "here: " << i << endl;
        strOut += "\n";
    }
    out << strOut;
	return out;
}
*/

// LeafNode Public:

// 
// Purpose: Default no arg constructor of LeafNode.
// Preconditon: No arguments in object creation.
// Postcondition: All variables of LeafNode are set to defaults.
LeafNode::LeafNode() : leftChild{ this }, rightChild{ this }, lThread{ false }, 
rThread{ false }
{}

// Purpose: Constructor with data in argument.
// Preconditon: Integer variable is argument in object creation.
// Postcondition: LeafNode variables are set to defaults but data is assigned
//                to newData input.
LeafNode::LeafNode(const int& newData) : data{newData}, leftChild{nullptr}, 
    rightChild{nullptr}, lThread{ false }, rThread{ false }
{}


// Purpose: Constructure with all variables argument.
// Preconditon: Argument has integer and two LeafNode pointers as argument, 
//              variables are also not null.
// Postcondition: All variables assigned to corresponding variables in LeafNode
LeafNode::LeafNode(const int& newData, LeafNode* leftPtr, LeafNode* rightPtr) : 
    data{newData}, leftChild{leftPtr}, rightChild{rightPtr}, 
    lThread{ false }, rThread{ false }
{}

// Purpose: 
// Preconditon:
// Postcondition: 
void LeafNode::setData(const int& newData) {
    data = newData;
}

// Purpose: 
// Preconditon:
// Postcondition: 
int LeafNode::getData() {
    return data;
}

// Purpose: 
// Preconditon:
// Postcondition: 
auto LeafNode::getLeftChildPtr() const {
    return leftChild;
}

// Purpose: 
// Preconditon:
// Postcondition: 
auto LeafNode::getRightChildPtr() const {
    return rightChild;
}

// Purpose: 
// Preconditon:
// Postcondition: 
void LeafNode::setLeftChild(LeafNode* leftLeaf) {
    leftChild = leftLeaf;
}

// Purpose: 
// Preconditon:
// Postcondition: 
void LeafNode::setRightChild(LeafNode* rightLeaf) {
    rightChild = rightLeaf;
}

// BSTree protected

// Deprecated method not used
// Purpose: Goes through the tree and returns the height of the longest branch
// Preconditon:
// Postcondition: 
int BSTree::getHeightHelper(LeafNode* subTreePtr) const {
    if (!subTreePtr->lThread || !subTreePtr->rThread) return 0;
    
    int leftHeight = getHeightHelper(subTreePtr->leftChild);
    int rightHeight = getHeightHelper(subTreePtr->rightChild);


    //returns the max of leftHeight and rightHeight (+ 1 to account for itself)
    return (leftHeight < rightHeight) ? rightHeight + 1: leftHeight + 1;
}
/*
 * deprecated
// toString all levels
string BSTree::toStringTree() {
    string s;
    int height = getHeightHelper(rootPtr);
    //cout << "here";
    for (int i = 0; i < height; i++) {
        s += toStringGivenLevel(rootPtr, i);
        s += "\n";
    }
    return s;
}
*/
// toString given a level
// Purpose: 
// Preconditon:
// Postcondition: 
string BSTree::toStringGivenLevel(LeafNode* root, int level, string strLevel) {
    //cout << "here now";
    if (root == rootPtr) return strLevel;
    if (level == 1) {
        strLevel += root->getData();
    }else if (level > 1) {
        toStringGivenLevel(root->leftChild, level - 1, strLevel);
        toStringGivenLevel(root->rightChild, level - 1, strLevel);
    }
    return strLevel;
}

// Purpose: 
// Preconditon:
// Postcondition: 
int BSTree::getNumOfNodesHelper(LeafNode* subTreePtr) const {
    if (subTreePtr == nullptr) return 0;
    int counter = 0;
    //Recursively traverse tree going left then right if have those children
    
    counter += getNumOfNodesHelper(subTreePtr->leftChild);
    counter += getNumOfNodesHelper(subTreePtr->rightChild);
  
    //Return the count (+1 to account for itself)
    return counter + 1;
}

// Purpose: 
// Preconditon:
// Postcondition: 
LeafNode* BSTree::findNode(LeafNode* treePtr, const int target) const {
    if (treePtr->data == target) return treePtr;
    //If there is nowhere to go then we have hit the bottom and have not found node.
    else if (treePtr->rThread == false && treePtr->lThread == false) return nullptr;

    else if (treePtr->data > target) return findNode(treePtr->leftChild, target);

    else if (treePtr->data < target) return findNode(treePtr->rightChild, target);

    //At this point, target was not in the tree and thus return null ptr
    return nullptr;
}

// Purpose: 
// Preconditon:
// Postcondition: 
LeafNode* BSTree::copyTree(LeafNode* oldTreeRootPtr) {
    if (oldTreeRootPtr == nullptr) return nullptr;
    LeafNode* temp;
    temp = oldTreeRootPtr;
    temp->leftChild = copyTree(oldTreeRootPtr->leftChild);
    temp->rightChild = copyTree(oldTreeRootPtr->rightChild);
    // clean up 
    delete temp;
    return oldTreeRootPtr;
}

void BSTree::preorder(void visit(int), LeafNode* treePtr) {

}

void BSTree::inorder(void visit(int), LeafNode* treePtr) {

}

void BSTree::postorder(void visit(int), LeafNode* treePtr) {

}

//BSTree public

// Purpose: 
// Preconditon:
// Postcondition: 
BSTree::BSTree() {
    //In the case of empty, root will be a dummy node
    rootPtr = new LeafNode();
}

// Purpose: 
// Preconditon:
// Postcondition: 
BSTree::BSTree(const int data) {
   //This method will add all values from 1 - data into BSTree

    //Dummy node
    rootPtr = new LeafNode();
    // only need to change lThread because rest are 
    // set to defaults in constructor
    rootPtr->lThread = true;
    //Call BalancedAdd to add all values into tree in correct order
    balancedAdd(1, data);

}

// Purpose: 
// Preconditon:
// Postcondition: 
void BSTree::balancedAdd(int start, int end) {
    // maybe check and set leafState in this metho
    if (start > end) return;

    int mid = (start + end) / 2;

    add(mid);
    // recursive bottom half
    balancedAdd(start, mid - 1);
    // recursive top half
    balancedAdd( mid + 1, end);

}

// Purpose: 
// Preconditon:
// Postcondition: 
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

// Purpose: 
// Preconditon:
// Postcondition: 
BSTree::BSTree(const int data, BSTree* leftTreePtr, BSTree* rightTreePtr) {
    rootPtr->data = data;
    rootPtr->leftChild = copyTree(leftTreePtr->rootPtr);
    rootPtr->rightChild = copyTree(rightTreePtr->rootPtr);
}

BSTree::BSTree(const BSTree* aTree) {
    
    rootPtr = copyTree(aTree->rootPtr);

}

// Purpose: 
// Preconditon:
// Postcondition: 
BSTree::~BSTree() {
    //clear(rootPtr);
    //delete rootPtr;
    //rootPtr = nullptr;
//    
//    LeafNode* del;
//    LeafNode* trav = rootPtr->leftChild;
//    // traverse tree
//    // delete nodes individually 
//    // until I hit the left most leaf keep looping
//    while (trav->lThread) {
//        trav = trav->leftChild;        
//    }
//    // while trav isnt root keep looping
//    while (trav != rootPtr) {
//        del = trav;
//        cout << " " << del->data;
//        trav = trav->rightChild;
//        //del = nullptr;
//        //delete del->leftChild;
//        //delete del->rightChild;
//        //delete del;
//    }
//    cout << endl;
//    
//
//    
}


//
// Purpose: 
// Preconditon:
// Postcondition: 
bool BSTree::isEmpty() const {
	return rootPtr == nullptr; // if root is nullptr then tree is empty
}

// Purpose: 
// Preconditon:
// Postcondition: 
int BSTree::getHeight() const {
    return getHeightHelper(rootPtr);
}

// Purpose: 
// Preconditon:
// Postcondition: 
int BSTree::getNumOfNodes() const {
    return getNumOfNodesHelper(rootPtr);
}

// Purpose: 
// Preconditon:
// Postcondition: 
int BSTree::getRootData() const {
    //Compensate for dummy node
	return rootPtr->leftChild->data;
}

// Purpose: 
// Preconditon:
// Postcondition: 
void BSTree::setRootData(const int newData) {
    //Compensate for dummy node
    rootPtr->leftChild->data = newData;
}

// Purpose: 
// Preconditon:
// Postcondition: 
bool BSTree::add(const int newData) {
    LeafNode* tempNode = new LeafNode(newData);
    //first check if tree is empty
    if ((rootPtr->leftChild == rootPtr) && (rootPtr->rightChild == rootPtr)) {
        //At this point the tree is empty and only has dummy node
        //Reroute all pointers of root to tempNode
        tempNode->leftChild = rootPtr->leftChild;
        tempNode->rightChild = rootPtr->rightChild;
        //Insert tempNode into tree
        rootPtr->leftChild = tempNode;
        rootPtr->lThread = true;
        return true;
    }
    //Tree is not empty so we will add it
    LeafNode* ptr = new LeafNode();
    //This will avoid the dummy node
    ptr = rootPtr->leftChild;
    //Keep looping until internally stopped by return
    while (true) {
        if (newData == ptr->data) return false; 
        //Do same thing if it is larger than the current node data
        if (newData > ptr->data) {
            if (ptr->rThread == false) {
                tempNode->rightChild = ptr->rightChild;
                tempNode->rThread = ptr->rThread;
                tempNode->lThread = false;

                //Point to inorder successor 
                tempNode->leftChild = ptr;
                ptr->rThread = true;
                ptr->rightChild = tempNode;
                return true;
            }
            else ptr = ptr->rightChild;
        }
        
        if (newData < ptr->data) {
            //In this case, we need to navigate left
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

// Purpose: 
// Preconditon:
// Postcondition: 
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
// Purpose: 
// Preconditon:
// Postcondition: 
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

// Purpose: 
// Preconditon:
// Postcondition: 
void BSTree::deleteOneChild(LeafNode* ptr, LeafNode* parent) {
    LeafNode* child;
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
    
    if (ptr->lThread) {
        predecessor->rightChild = successor;
    }
    else if (ptr->rThread) successor->leftChild = predecessor;
    
    delete ptr;
}

// Purpose: 
// Preconditon:
// Postcondition: 
void BSTree::deleteTwoChild(LeafNode* ptr, LeafNode* parent) {
    
    LeafNode* successor = ptr->rightChild;
    LeafNode* parentSuccessor = ptr;

    while (successor->lThread) {
        parentSuccessor = successor;
        successor = successor->leftChild;

    }
    ptr->data = successor->data;
    
    if ((!successor->lThread) && !(successor->rThread)) deleteNoChild(successor, parentSuccessor);

    else deleteOneChild(successor, parentSuccessor);
}


// 
// Purpose: 
// Preconditon:
// Postcondition: 
void BSTree::clear(LeafNode* trav) {
    //trav is the most left node
    if(rootPtr->leftChild!=rootPtr){
        LeafNode* ptr;
        ptr = rootPtr->leftChild;
        while (ptr->lThread) {
            ptr = ptr->leftChild;
        }
        LeafNode* deleteNode = ptr;
        while (ptr != rootPtr) {
            
            ptr = inorderSuccessor(ptr);
            delete deleteNode;
            deleteNode = nullptr;
            
        }
    }
    delete rootPtr;
    rootPtr = nullptr;
   
    //while (trav->lThread) {
    //    trav = trav->leftChild;
    //}
    ////Now trav is the most left node
    //bool hitRoot = false;
    //while (trav != rootPtr) {
    //    trav = inorderSuccessor(trav);
    //    LeafNode* previous = inorderPredecessor(trav);
    //    previous = nullptr;
    //    delete previous;
    //    delete trav->leftChild;
    //}




    /*if (trav != rootPtr) {
        if (trav->lThread) {
            clear(trav->leftChild);
        }
        if (trav->rThread) {
            clear(trav->rightChild);
        }
        cout << " " << trav->data; 
        trav = nullptr;
        delete trav;
    }*/
    //
    /*
    // go to left most node
    while (trav->lThread) {
        trav = trav->leftChild;
    }
    */
}

// Purpose: 
// Preconditon:
// Postcondition: 
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

// Purpose: 
// Preconditon:
// Postcondition: 
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

// Purpose: 
// Preconditon:
// Postcondition: 
bool BSTree::contains(const int anEntry) const {
    //Return true if findNode returns a ptr and false if returns nullptr
    return (findNode(rootPtr->leftChild, anEntry) != nullptr) ? true : false;
}

// Purpose: 
// Preconditon:
// Postcondition: 
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

// Purpose: 
// Preconditon:
// Postcondition: 
BSTree& BSTree::operator= (const BSTree& rightHandSIde) {
    return *this;
}
