#ifndef _GENERALTREE_H
#define _GENERALTREE_H

#include <cstdlib>
#include <exception>
#include <iostream>
#include <set>

//  This is the node class with two variables, a value variable, and
//a set of Nodes variable
class Node {
    
public:
    
    Node() : children(){}
    char value;
    std::set<Node*> children;
    
};

class GeneralTree {
    
public:
    //  Default General Tree constructor
    
    GeneralTree();
    
    //  General Tree constructor that takes another tree as a paremeter
    //and returns the Tree
    
    GeneralTree(const GeneralTree& other);
    
    //General Tree destructor
    
    ~GeneralTree();
    
    //  This overloads the equals operator. It replaces the General Tree on
    //the left side of the equal sign with the one on the right
    
    GeneralTree& operator=(const GeneralTree& other);
    
    //  This method inserts a new node with the given value underneath the
    //parent given
    
    Node* insert(char value, Node* parent);
    
    //This method simply prints the tree.
    
    void print() const;
    
private:
    
    // This method recursively finds where the parent is located in the tree
    
    Node* findParent(Node* starting, const Node* parent);
    
    //  This method takes the parameter from print and begins printing from
    //that location
    
    void printFrom(Node* start) const;
    
    // The start node
    
    Node* start;
    
    //  This method deletes all the nodes from the tree
    
    void clear();
    
    // This method begins copys data from another tree
    
    void copyOther(const GeneralTree& other);
    
    //  This method copys from the given parent node into the start node
    
    void copyFrom(Node* start, Node* parent);
    
    // This method clears from the given start node

    void clearFrom(Node* start);
};
#endif