#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// M M
//  A
// S S
bool top_XMAS(vector<string> grid, int row, int col) {
    bool fits_mask = true;

    fits_mask &= grid[row].substr(col, 1) == "M";
    fits_mask &= grid[row].substr(col+2, 1) == "M";

    fits_mask &= grid[row+1].substr(col+1, 1) == "A";

    fits_mask &= grid[row+2].substr(col, 1) == "S";
    fits_mask &= grid[row+2].substr(col+2, 1) == "S";

    return fits_mask;
} 

// S S
//  A
// M M
bool bottom_XMAS(vector<string> grid, int row, int col) {
    bool fits_mask = true;

    fits_mask &= grid[row].substr(col, 1) == "S";
    fits_mask &= grid[row].substr(col+2, 1) == "S";

    fits_mask &= grid[row+1].substr(col+1, 1) == "A";

    fits_mask &= grid[row+2].substr(col, 1) == "M";
    fits_mask &= grid[row+2].substr(col+2, 1) == "M";

    if (fits_mask)
        return true;

    return false;
} 

// M S
//  A
// M S
bool left_XMAS(vector<string> grid, int row, int col) {
    bool fits_mask = true;

    fits_mask &= grid[row].substr(col, 1) == "M";
    fits_mask &= grid[row].substr(col+2, 1) == "S";

    fits_mask &= grid[row+1].substr(col+1, 1) == "A";

    fits_mask &= grid[row+2].substr(col, 1) == "M";
    fits_mask &= grid[row+2].substr(col+2, 1) == "S";

    if (fits_mask)
        return true;

    return false;
} 

// S M
//  A
// S M
bool right_XMAS(vector<string> grid, int row, int col) {
    bool fits_mask = true;

    fits_mask &= grid[row].substr(col, 1) == "S";
    fits_mask &= grid[row].substr(col+2, 1) == "M";

    fits_mask &= grid[row+1].substr(col+1, 1) == "A";

    fits_mask &= grid[row+2].substr(col, 1) == "S";
    fits_mask &= grid[row+2].substr(col+2, 1) == "M";

    if (fits_mask)
        return true;

    return false;
} 


int main() {

    ifstream myFile("input4.txt");
    string line;
    int first, second;

    vector<string> word_search;

    int count = 0;

    while(getline(myFile, line)) {
        word_search.push_back(line);
    }

    

    int rows = word_search.size();
    int cols = word_search[0].length(); // Assuming rectangular
    // cout << rows << " " << cols << endl;

    for (int row = 0; row < rows - 2; row++) {
       for (int col = 0; col < cols - 2; col++) {

            if (top_XMAS(word_search, row, col))  {
                // cout << "TOP" << endl;
                count++;
            }
            if (bottom_XMAS(word_search, row, col)) {
                // cout << "BOTTOM" << endl;
                count++;
            }
            if (left_XMAS(word_search, row, col)) {
                // cout << "LEFT" << endl;
                count++;
            }
            if (right_XMAS(word_search, row, col)) {
                // cout << "RIGHT" << endl;
                count++;
            }
        }           
    }

    cout << count << endl;




    return 0;
}