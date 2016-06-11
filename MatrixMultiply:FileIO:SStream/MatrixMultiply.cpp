#include <cstdlib>
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
/* This method takes two integers, one of them being rows and the other
 being columns and returns a vector of vectors<int>. It first constructs a 
 vector of vectors then puts one vector in each row and fills that vector
 up with the remaining columns of each row. It asks the user to input an integer
 for ij position of the matrix.
 */
vector<vector<int>> makeMatrix(int rows, int cols) {
    vector< vector<int> > matrix;
    
    for (int row = 0; row < rows; row++) {
        matrix.push_back(vector<int>());
        
        for (int col = 0; col < cols; col++) {
            int temp;
            cout << "element of row " << (row + 1) << " column " << (col+1) << ": ";
            while(!(cin>>temp)){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  //Ignores anything other than integers
                cout << "Enter a valid number for " << (row + 1) << " column " << (col+1) << ": ";
            }
            matrix[row].push_back(temp);
        }
    }
    return matrix;
}
/* This method simply asks for the dimensions of the matrix
 */
void getDimensions(int arr[]) {
    int temp;
    cout << "Enter row dimension: ";
    while(!(cin>>temp)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  //Ignores anything other than integers
        cout << "Enter a valid number for row dimension: ";
    }
    arr[0] = temp;
    cout << "Enter column dimension: ";
    while(!(cin>>temp)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  //Ignores anything other than integers
        cout << "Enter a valid number for column sdadimension: ";
    }
    arr[1] = temp;
}
/* This method takes two parameters, two vector matrixes, and returns a vector matrix that is 
 the vector product of the two matrixes. c in the second for loop iterates vertically across one 
 column of the second matrix and iterates horizontally across one row of the first matrix. Both the for
 loops simply iterate over column and row size of the new matrix.
 */
vector<vector<int>> matrixMult(vector<vector<int>>& matrix1,vector<vector<int>>& matrix2) {
    vector<vector<int>> newMatrix(matrix1.size(),vector<int>(matrix1.size()));
    int summ = 0;
    for(int i = 0; i < matrix1.size();i++){
        for(int j = 0; j < matrix2[0].size();j++) {
            int c = 0;
            while(c < matrix1[0].size()) {
                summ += (matrix1[i][c] * matrix2[c][j]);
                c +=1;
            }
            newMatrix[i][j] = summ;
            summ = 0;
        }
    }
    return newMatrix;
}
/* This method simply loops through the matrix printing it's contents
*/
void printMatrix(vector<vector<int>>& matrix) {
    for (int row = 0; row < matrix.size(); row++) {
        for (int col = 0; col < matrix[0].size(); col++) {
            if(col == 0) {
                cout  << "     |" << matrix[row][col];
            }
            else {
                cout  << "|    |" << matrix[row][col];
            }
            
        }
        cout << "|" << endl;
    }
}
/* The main function calls for the dimensions of both matrixes then creates both of them. It then
 checks if it is possible to multiply both matrixes and that the rows and columns are greater than 0. 
 Calling the matrixMult function then printing it's contents*/
int main() {
    int dimensions[2];
    cout << "Matrix 1 " << endl;
    getDimensions(dimensions);
    if(dimensions[0] < 1 || dimensions[1] < 1) {
        cout << "Rows and columns must be greater than 0" << endl;
        return 0;
    }
    vector<vector<int>> matrix1 = makeMatrix(dimensions[0],dimensions[1]);
    cout << "Matrix 2 " << endl;
    getDimensions(dimensions);
    if(dimensions[0] < 1 || dimensions[1] < 1) {
        cout << "Rows and columns must be greater than 0" << endl;
        return 0;
    }
    vector<vector<int>> matrix2 = makeMatrix(dimensions[0],dimensions[1]);
    if(matrix1.size() != matrix2[0].size()) {
        cout << "You cannot multiply matrixes of these dimensions" << endl;
        return 0;
    }
    cout << setw(5);
    vector<vector<int>> matrix3 = matrixMult(matrix1,matrix2);
    printMatrix(matrix3);
    return 0;

}


