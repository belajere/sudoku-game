#include <iostream>
#include <vector>
using namespace std;


class Cell {
    private: 
        int value; // stores the value
        bool isFixed; //  indicates if the cell is pre-filled and unchangeable.
    public:
        Cell() : value(0), isFixed(false) {}
        
        int getValue() const { return value; } //returns the cell value.
        void setValue(int v) { value = v; } // sets the cell value
        
        bool getIsFixed() const { return isFixed; } // returns if the cell is fixed
        void setIsFixed(bool fixed) { isFixed = fixed; } // sets the cell's fixed status
};
class Board {
    private: 
        Cell cells [4][4];
        
        bool isValid(int row, int col, int num) { //  Checks if placing a number in a given cell is valid 
        // Check row
        for (int x = 0; x < 4; x++) {
            if (cells[row][x].getValue() == num) {
                return false;
            }
        }
        // Check column
        for (int x = 0; x < 4; x++) {
            if (cells[x][col].getValue() == num) {
                return false;
            }
        }
        // Check 2x2 box
        int startRow = row - row % 2, startCol = col - col % 2;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                if (cells[i + startRow][j + startCol].getValue() == num) {
                    return false;
                }
            }
        }
        return true;
    }
        
public:
    void initialize(const vector<vector<int> >& presetValues) {  // preset values
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (presetValues[i][j] != 0) {
                    cells[i][j].setValue(presetValues[i][j]);
                    cells[i][j].setIsFixed(true);
                }
            }
        }
    }
    void print() const {  // current state 
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                cout << cells[i][j].getValue() << " ";
            }
            cout << endl;
        }
    }
    
    
    bool setCellValue(int row, int col, int value) { //Sets the value of cell if it's valid and not fixed.
        if (!cells[row][col].getIsFixed() && isValid(row, col, value)) {
            cells[row][col].setValue(value);
            return true;
        }
        return false;
    }
    
    bool isComplete() const { // Checks if the Sudoku puzzle is complete.

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (cells[i][j].getValue() == 0) {
                    return false;
                }
            }
        }
        return true;
    }
    
};

int main() {
    
    Board board;


    vector<vector<int> > presetValues(4, vector<int>(4, 0));
    presetValues[0][0] = 1;
    presetValues[1][2] = 2;
    presetValues[2][1] = 3;
    presetValues[3][3] = 4;

    board.initialize(presetValues);
    cout << "Initial Sudoku Grid:" << endl;
    board.print();

    while (!board.isComplete()) {
        int row, col, value;
        cout << "Enter row (0-3), column (0-3) and value (1-4): ";
        cin >> row >> col >> value;

        if (board.setCellValue(row, col, value)) {
            cout << "Updated Sudoku Grid:" << endl;
            board.print();
        } else {
            cout << "Invalid move. Try again." << endl;
        }
    }

    cout << "Congratulations! You have completed the Sudoku puzzle." << endl;

    return 0;
    
}