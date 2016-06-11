#ifndef _GRAPH_H
#define _GRAPH_H

#include <cstdlib>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stdexcept>
#include <stack>
#include <set>

/*
 * Exception for trying to find
 * a path between two nodes if
 * at least one of the nodes
 * doesn't exist.
 */
class NonExistentNodeException : public std::exception
{
public:
    virtual const char* what() const throw() {
        return "At least one of those nodes doesn't exist!";
    }
};

/*
 * Exception for trying to find
 * a path between two nodes when
 * no path exists.
 */
class NoPathException : public std::exception
{
public:
    virtual const char* what() const throw() {
        return "No path exists between those two nodes!";
    }
};

/*
 * Node
 * -----
 * Represents a node in a graph. T is
 * the type of value held in the node.
 */
template <typename T>
class Node
{
public:
    Node(const T& value) : value(value) {}
    
    /*
     * Why is an unordered_set better than
     * a vector for the list of adjacent
     * nodes?
     */
    std::unordered_set<Node<T>*> adjacents;
    T value;
    bool marked;
};

/*
 * Graph
 * -----
 * Represents a bi-directional (undirected)
 * graph. Nodes can have values of any type,
 * so long as that type:
 *   - can be used as a key in a map, and;
 *   - can be inserted into cout.
 *
 * The graph does not have to be connected.
 * Values must be unique.
 */
template <typename T>
class Graph
{
public:
    Graph() {}
    
    /*
     * Since we dynamically allocate each node,
     * we need the big 3!
     *
     * - destructor
     * - copy constructor
     * - assignment operator
     */
    ~Graph() {
        clear();
    }
    
    Graph(const Graph<T>& other) {
        copyOther(other);
    }
    
    Graph<T>& operator=(const Graph<T>& other) {
        if (this != &other) {
            clear();
            copyOther(other);
        }
        return *this;
    }
    
    /*
     * Common graph operations.
     */
    
    Node<T>* insert(const T& value) {
        if (nodes.find(value) != nodes.end()) {
            return NULL;
        }
        
        Node<T>* newNode = new Node<T>(value);
        nodes[value] = newNode;
        return newNode;
    }
    
    // Two versions of connect! One that takes
    // node pointers, another that takes node
    // values.
    void connect(Node<T>* first, Node<T>* second) {
        first->adjacents.insert(second);
        second->adjacents.insert(first);
    }
    
    void connect(const T& first, const T& second) {
        if (nodes.find(first) == nodes.end() ||
            nodes.find(second) == nodes.end()) {
            throw NonExistentNodeException();
        }
        
        connect(nodes[first], nodes[second]);
    }
    
    // Unmarks all nodes. Important for the shortest
    // path algorithm!
    void unmarkAll() {
        for (auto iter = nodes.begin();
             iter != nodes.end();
             iter++) {
            iter->second->marked = false;
        }
    }
    
    // Prints a list of nodes in the graph, and
    // prints a list of adjacent nodes next to each
    // node.
    void print() {
        for (auto iter = nodes.begin();
             iter != nodes.end();
             iter++) {
            std::cout << iter->first << ": ";
            
            for (auto neighborsIter = iter->second->adjacents.begin();
                 neighborsIter != iter->second->adjacents.end();
                 neighborsIter++) {
                
                std::cout << (*neighborsIter)->value << " ";
            }
            std::cout << std::endl;
        }
    }
    
    std::vector<Node<T>*> shortestPath(const T& start, const T& end) {
        
        // This checks to see if the either node exists in the graph
        
        if(nodes.count(start) == 0 or nodes.count(end) == 0) {
            throw NonExistentNodeException();
        }
        // This method unmarks all the nodes
        
        unmarkAll();
        
        // Frame contains all possibel traversals from the start node to
        //the end node. Check is a unique set made to make sure no paths are
        //tried twice. Stack contains all possible node to node traversals at
        //each iteration.
        
        std::vector<std::vector<Node<T>*> > frame;
        std::set<Node<T>*> check;
        std::queue<Node<T>*> stack;
        
        //  Begin by pushing all adjacent nodes on to a new vector of nodes (a path)
        //and checks to see if the end node is one of these initial adjacent ones.
        //Finally each of these vector nodes is pushed onto a frame that contains all
        //possible paths and each node is pushed onto a stack and instead into check

        for(Node<T>* x : nodes[start]->adjacents) {
            if(x->value != " "){
                std::vector<Node<T>*> temp;
                temp.push_back(nodes[start]);
                temp.push_back(x);
                if(x->value == end) {
                    return temp;
                }
                stack.push(x);
                check.insert(x);
                frame.push_back(temp);
            }
        }
        
        // Marks the start node
        
        nodes[start]->marked = true;
        
        // Checks to see if stack is empty
        
        while(!stack.empty()) {
            
            //  If the current node being looked at is the end node
            //Called shortPath to find the shortest of possible paths
            
            if(stack.front()->value == end) {
                return shortPath(frame, end);
            }
            //  Temps holds onto all temporary paths for each iteration

            std::vector<std::vector<Node<T>*> > temps;
            
            // This iteration checks through each possible path
            
            for(std::vector<Node<T>*> x : frame) {
                if(!x.empty()) {
                    
                    // checks to see if the end node of the path matches the node
                    //on the stack
                    
                    if(x.back() == stack.front()){
                        
                        //  This loop will create a new path for each of the matching
                        //nodes adjacents and added to temps
                        
                        for(Node<T>* y : stack.front()->adjacents) {
                            if(y->marked == false){
                                std::vector<Node<T>*> temp = x;
                                temp.push_back(y);
                                temps.push_back(temp);
                            }
                        }
                        // This method erases the old path, seeing as the old path is
                        //redundant with the newly created longer paths. It also erases
                        //paths that will never reach the end
                        
                        frame.erase(remove(frame.begin(),frame.end(),x),frame.end());
                    }
                }
            }
            
            // Pushes all adjacent nodes onto the stack that haven't already
            //been added.
            
            for(Node<T>* y : stack.front()->adjacents) {
                if(y->marked == false && check.count(y) == 0) {
                    check.insert(y);
                    stack.push(y);
                }
            }
            
            // This pushes all newly made paths onto frame.
            
            for(std::vector<Node<T>*> x : temps) {
                frame.push_back(x);
            }
            // Marks the Node that was checked, then pops.
            stack.front()->marked = true;
            stack.pop();
            
            // If the stack is empty then there is no possible path.
            //So we throw an exception.
            if(stack.empty()) {
                throw NoPathException();
            }
        }

        return std::vector<Node<T>*>();
    }

private:
    std::unordered_map<T, Node<T>*> nodes;  // for uniqueness and lookup
    
    void copyOther(const Graph<T>& other) {
        
        // First, insert each node as an island
        // (no edges yet).
        for (auto iter = other.nodes.begin();
             iter != other.nodes.end();
             iter++) {
            insert(iter->first);
        }
        
        // Then, connect each pair of nodes that
        // has an edge in the other graph.
        for (auto iter = other.nodes.begin();
             iter != other.nodes.end();
             iter++) {
            auto adjacents = iter->second->adjacents;
            for (auto neighborsIter = adjacents.begin();
                 neighborsIter != adjacents.end();
                 ++neighborsIter) {
                // Need to connect the values here!
                // Connecting iter->second and *neighborsIter
                // would re-connect the nodes in the old graph
                // (so this would do nothing)
                connect(iter->first, (*neighborsIter)->value);
            }
        }
    }
    
    void clear() {
        for (auto iter = nodes.begin();
             iter != nodes.end();
             iter++) {
            delete iter->second;
        }
        
        nodes.clear();
    }
    std::vector<Node<T>*> shortPath(std::vector<std::vector<Node<T>*> > frame, const T& end) {
        std::vector<Node<T>*> shortest;
        for(std::vector<Node<T>*> x : frame) {
            if(x.back()->value == end) {
                if(shortest.empty()) {
                    shortest = x;
                }
                else if(shortest.size() > x.size()) {
                    shortest = x;
                }
            }
        }
        return shortest;
    }
};

#endif