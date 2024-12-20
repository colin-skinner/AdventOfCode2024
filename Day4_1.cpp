#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool horizontal_XMAS(vector<string> grid, int row, int col) {

    if (grid[row].substr(col, 4) == "XMAS" ||
        grid[row].substr(col, 4) == "SAMX")
        return true;

    return false;
} 

bool vertical_XMAS(vector<string> grid, int row, int col) {
    string xmas = "";

    xmas += grid[row].substr(col, 1);
    xmas += grid[row+1].substr(col, 1);
    xmas += grid[row+2].substr(col, 1);
    xmas += grid[row+3].substr(col, 1);

    if (xmas == "XMAS" ||
        xmas == "SAMX")
        return true;

    return false;
} 

bool forward_slash_XMAS(vector<string> grid, int row, int col) {
    string xmas = "";

    xmas += grid[row].substr(col, 1);
    xmas += grid[row-1].substr(col+1, 1);
    xmas += grid[row-2].substr(col+2, 1);
    xmas += grid[row-3].substr(col+3, 1);

    if (xmas == "XMAS" ||
        xmas == "SAMX")
        return true;

    return false;
} 

bool back_slash_XMAS(vector<string> grid, int row, int col) {
    string xmas = "";

    xmas += grid[row].substr(col, 1);
    xmas += grid[row+1].substr(col+1, 1);
    xmas += grid[row+2].substr(col+2, 1);
    xmas += grid[row+3].substr(col+3, 1);

    if (xmas == "XMAS" ||
        xmas == "SAMX")
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

    // Horizontal
    for (int row = 0; row < rows; row++) {
       for (int col = 0; col < cols - 3; col++) {
            if (horizontal_XMAS(word_search, row, col))
                count++;
        } 
    }

    
    // cout << count << endl;

    // Vertical
    for (int row = 0; row < rows - 3; row++) {
       for (int col = 0; col < cols; col++) {
            if (vertical_XMAS(word_search, row, col))
                count++;
        } 
    }

    // cout << count << endl;

    // Forward Slash (starts bottom left)
    for (int row = 3; row < rows; row++) {
       for (int col = 0; col < cols - 3; col++) {
            if (forward_slash_XMAS(word_search, row, col))
                count++;
        } 
    }

    // cout << count << endl;

    // Back Slash (starts top left)
    for (int row = 0; row < rows - 3; row++) {
       for (int col = 0; col < cols - 3; col++) {
            if (back_slash_XMAS(word_search, row, col))
                count++;
        } 
    }

    cout << count << endl;




    return 0;
}