#include "Graph.h"
using namespace std;

int main()
{
    // Create a graph
    Graph<string> g;
    Node<string>* a = g.insert("a");
    Node<string>* b = g.insert("b");
    Node<string>* c = g.insert("c");
    Node<string>* d = g.insert("d");
    Node<string>* e = g.insert("e");
    g.connect(a, b);
    g.connect(c, d);
    g.connect(b, e);
    g.connect(c, e);
    cout << "Graph 1" << endl;
    g.print();
    cout << "-----" << endl;
    vector<Node<string>*> path = g.shortestPath("a", "e");
    
    cout << "Graph 1: path from a to e: ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i]->value << " ";
    }
    cout << endl;
    cout << "----" << endl;
    
    // Create a larger graph with unconnected nodes
    
    Graph<string> g2;
    Node<string>* ai = g2.insert("a");
    Node<string>* bi = g2.insert("b");
    Node<string>* ci = g2.insert("c");
    Node<string>* di = g2.insert("d");
    Node<string>* ei = g2.insert("e");
    Node<string>* fi = g2.insert("f");
    Node<string>* gi = g2.insert("g");
    Node<string>* hi = g2.insert("h");
    Node<string>* i = g2.insert("i");
    Node<string>* j = g2.insert("j");
    Node<string>* k = g2.insert("k");
    Node<string>* l = g2.insert("l");
    Node<string>* m = g2.insert("m");
    Node<string>* n = g2.insert("n");
    Node<string>* o = g2.insert("o");
    Node<string>* p = g2.insert("p");
    Node<string>* q = g2.insert("q");
    Node<string>* r = g2.insert("r");
    Node<string>* s = g2.insert("s");
    Node<string>* t = g2.insert("t");
    Node<string>* u = g2.insert("u");
    Node<string>* v = g2.insert("v");
    Node<string>* w = g2.insert("w");
    Node<string>* x = g2.insert("x");
    
    g2.connect(ai,bi);
    g2.connect(bi,ci);
    g2.connect(ci,di);
    g2.connect(di,ei);
    g2.connect(ei,fi);
    g2.connect(ei, j);
    g2.connect(ei, ai);
    g2.connect(fi, m);
    g2.connect(j, i);
    g2.connect(j, p);
    g2.connect(j, di);
    g2.connect(i, ci);
    g2.connect(ci, ai);
    g2.connect(l, k);
    g2.connect(k, o);
    g2.connect(o, hi);
    g2.connect(hi, m);
    g2.connect(m, n);
    g2.connect(n, o);
    g2.connect(o, p);
    g2.connect(p, q);
    g2.connect(q, r);
    g2.connect(r, t);
    g2.connect(t, u);
    g2.connect(u, v);
    g2.connect(v, w);
    g2.connect(w, x);
    
    
    
    cout << "Graph Test" << endl;
    g2.print();
    cout << "-----" << endl;
    
    // This should output a e j p q r t u v w x
    
    vector<Node<string>*> path2 = g2.shortestPath("a", "x");
    
    //  This will throw an exception, no path exists!
    //vector<Node<string>*> noPath = g2.shortestPath("a", "g");
    
    cout << "Graph Test: path from a to e: ";
    for (int i = 0; i < path2.size(); i++) {
        cout << path2[i]->value << " ";
    }
    cout << endl;
    cout << "----" << endl;
    
    // Create another graph, which is initially
    // just a copy of the first graph, and connect
    // "a" and "e" directly.
    Graph<string> gO(g);
    gO.connect(a, e);
    cout << "Graph 1 again" << endl;
    gO.print();
    cout << "-----" << endl;
    cout << "Graph 2" << endl;
    gO.print();
    cout << "-----" << endl;
    
    // Find the shortest path from "a" to "e"
    // in both graphs.
    path = g.shortestPath("a", "e");
    cout << "Graph 1: path from a to e: ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i]->value << " ";
    }
    cout << endl;
    cout << "----" << endl;
    
    path = gO.shortestPath("a", "e");
    cout << "Graph 2: path from a to e: ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i]->value << " ";
    }
    cout << endl;
    cout << "----" << endl;
    
    // Create a third graph.
    Graph<string> g3;
    g3.insert("z");         // this should get overwritten
    g3.insert("y");         // and this
    g3.connect("y", "z");   // also this
    
    // Set the third graph equal to the first
    // graph (making it a copy of the first
    // graph).
    g3 = g;
    g3.connect("a", "e");
    cout << "Graph 1 a third time" << endl;
    g.print();
    cout << "-----" << endl;
    cout << "Graph 3" << endl;
    g3.print();
    cout << "-----" << endl;
    
    // Find the shortest path from "a" to "e"
    // in the first and third graphs.
    path = g.shortestPath("a", "e");
    cout << "Graph 1: path from a to e: ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i]->value << " ";
    }
    cout << endl;
    cout << "----" << endl;
    
    path = g3.shortestPath("a", "e");
    cout << "Graph 3: path from a to e: ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i]->value << " ";
    }
    cout << endl;
    cout << "----" << endl;
    
    return 0;
}