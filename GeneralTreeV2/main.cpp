#include "GeneralTree.h"
#include <sstream>
#include <exception>


using namespace std;

void parseRecursive(stringstream& ss, GeneralTree& gt, Node* parent)
{
    char nextChar;
    while (true) {
        ss >> nextChar;
        if (ss.fail())
            return;
        
        if (nextChar == ')')
            return;
        
        if (nextChar == '(') {
            Node* newNode = gt.insert(' ', parent);
            parseRecursive(ss, gt, newNode);
        } else {
            gt.insert(nextChar, parent);
        }
    }
}

void parseExpression(const string& expr, GeneralTree& gt)
{
    stringstream ss;
    ss << expr;
    
    parseRecursive(ss, gt, NULL);
}
void test() {
    // This should print:
    // (c(ab))
    GeneralTree gt;
    Node* grandparent = gt.insert('.', NULL);
    Node* parent1 = gt.insert('c', grandparent);
    Node* parent2 = gt.insert('.', grandparent);
    Node* kid1 = gt.insert('a', parent2);
    Node* kid2 = gt.insert('b', parent2);
    gt.print();
    cout << endl;
    
    // This should print:
    // (abab(cd)d(ef(g(h))))
    GeneralTree gt2;
    parseExpression("(abab(cd)d(ef(g(h))))", gt2);
    gt2.print();
    cout << endl;
    
    // This should print:
    // (c(ab))
    GeneralTree gt3 = gt;
    gt3.print();
    cout << endl;
    
    // This should print:
    // (abab(cd)d(ef(g(h))))
    GeneralTree gt4(gt2);
    gt4.print();
    cout << endl;
    
    // This should output
    // (adasda(bdas(dasc(esa(afasf(g(hdfasfi))das))fasf)))
    GeneralTree gt5;`
    parseExpression("((adasda(bdas(dasc(esa(afasf(g(hdfasfi))das))fasf)))", gt5);
    gt5.print();
    cout << endl;
    
    //  Change gt5 to gt3
    //  gt5 should now output (c(ab))
    gt5 = gt3;
    gt5.print();
    cout << endl;
    
    //  This should output
    //  () empty tree
    GeneralTree gt6;
    parseExpression("()", gt6);
    gt6.print();
    cout << endl;
    
    // This should print:
    // ((o)(d)(x))
    GeneralTree gt7;
    Node* grandparent7 = gt7.insert(' ', NULL);
    //This should throw an error/ Node* parent6 = gt7.insert('a',NULL);
    Node* parent7 = gt7.insert(' ', grandparent7);
    Node* parent8 = gt7.insert(' ', grandparent7);
    Node* parent9 = gt7.insert(' ', grandparent7);
    Node* kid7 = gt7.insert('o', parent7);
    Node* kid8 = gt7.insert('d', parent8);
    Node* kid9 = gt7.insert('x', parent9);
    //This should throw an error/  Node* kid9 = gt7.insert('d',parent2);
    gt7.print();
    cout << endl;

    
}
int main()
{
    test();
}