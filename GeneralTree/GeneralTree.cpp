

#include <iostream>
#include "GeneralTree.h"
#include <exception>
#include <set>
#include <stack>

using namespace std;

//  This class throws an exception when the Parent given to the insert method is
//NULL, but the start Node is not NULL. It is also thrown if you try to insert a
//character under a parent that holds a character value

class NullParentException: public exception {
    virtual const char* what() const throw(){
        return "Parent is NULL and start is not NULL. Or you are trying to insert a character under a non-parent (has character value)";
    }
};

//  This class throws an exception when the Parent given does not exist in
//the tree

class NoParentException: public exception {
    virtual const char* what() const throw(){
        return "Parent does not exist in this tree";
    }
};
// Basic Consctructor that sets the start node to NULL

GeneralTree::GeneralTree() : start(NULL) {}
// This constructor recieves another tree as it's parameter and sets
//the start node to null. It then calls copyOther

GeneralTree::GeneralTree(const GeneralTree& other) : start(NULL) {
    
    copyOther(other);
}
// This Method checks first to see if the two trees are equal to each other
//if not, it calls the clear method then the copyOther method

GeneralTree& GeneralTree::operator=(const GeneralTree &other) {
    if(this != &other) {
        clear();
        copyOther(other);
    }
    return *this;
}
// This is the General Tree destructor that clears all the nodes in the
//tree then sets start to NULL.

GeneralTree::~GeneralTree() {
    clear();
    start=NULL;
}
//This method calls clearFrom giving the start node as a parameter.

void GeneralTree::clear() {
    clearFrom(start);
    start=NULL;
}
//This method calls printFrom giving the start node as a parameter.

void GeneralTree::print() const {
    printFrom(start);
}
//This method inserts the given value into the Tree underneath the
//specified parent. It first checks to see if both parent and start
//are NULL. In that case the Tree is empty and just makes the parent
//the start node. The other case throws an exception if parent is NULL
//but start is not. Otherwise it checks to see if start is equal to parent
//if not it calls the findParent method. Afterwards it inserts the new node
//with value into the parent's children.

Node* GeneralTree::insert(char value, Node* parent) {
    if(parent == NULL and start == NULL) {
        Node* child = new Node();
        child->value = value;
        start = child;
        return child;
    }
    else if((parent == NULL and start !=  NULL)){
        throw NoParentException();
    }
    if(parent != start){
        if(isalpha(parent->value)) {
            throw NullParentException();
        }
        Node* temp = findParent(start, parent);
        if(temp == start) {
            throw NullParentException();
        }
        Node* child = new Node();
        child->value = value;
        temp->children.insert(child);
        temp = NULL;
        return child;
    }
    else {
        Node* child = new Node();
        child->value = value;
        start->children.insert(child);
        return child;
    }
    
}
//  This method is given a starting mode and a parent node. It traverses
//each set of children in reverse by using a stack until it find a match.
//If no match is found it returns NULL then an exception is thrown.

Node* GeneralTree::findParent(Node* starting,const Node* parent) {
    stack<Node*> stack;
    stack.push(starting);
    while(starting != parent) {
        if(!starting->children.empty()){
            for(Node* x : starting->children) {
                stack.push(x);
            }
            starting = stack.top();
            stack.pop();
        }
        else {
            if(stack.empty()) {
                throw NoParentException();
            }
            starting = stack.top();
            stack.pop();
        }
    }
    return starting;
}
//This method simply recursively deletes every Node in the Tree

void GeneralTree::clearFrom(Node* start) {
    if(start == NULL) {
        return;
    }
    for(Node* x : start->children) {
        clearFrom(x);
    }
    delete start;
}
//  This method calls copyFrom with the start node of this tree and
//other

void GeneralTree::copyOther(const GeneralTree& other) {
    copyFrom(other.start, start);
}
//  This method recursively copies into the parent node with the
//starting value. Each call it either simply calls insert, or if
//the value is not a letter, sets the parent node to the Node returned
//by the insert method.
void GeneralTree::copyFrom(Node* starting, Node *parent) {
    if(starting != NULL) {
        if(!isalpha(starting->value)){
            parent = insert(starting->value, parent);
        }
        else {
            insert(starting->value, parent);
        }
        for(Node* x : starting->children) {
                copyFrom(x, parent);
        }
    }
    
}

//  This method recursively prints the tree and adds parenthesis
//to show the depth of the characters.
void GeneralTree::printFrom(Node* starting) const
{
    if(!isalpha(starting->value)) {
        cout << "(";
    }
    else {
        cout << starting->value;
    }
    if(starting == NULL) {
        return;
    }
    else {
        for(Node* x : starting->children) {
            printFrom(x);
        }
    }
    if(!isalpha(starting->value)){
        cout << ")";
    }
}