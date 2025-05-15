#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cassert>
using namespace std;

void print_vec(vector<char> vec) {
    for (auto element : vec) {
        cout << element;
    }
    cout << endl;
}

void print_tiles(vector< vector<char> > vec) {
    for (auto element : vec) {
        print_vec(element);
    }
    cout << endl;
}

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct Coord {
    int row;
    int col;
    Direction dir;
    
    void next_coord(int& next_row, int& next_col) {

        switch(dir) {
        case UP:
            next_row = row - 1;
            next_col = col;
            return;
        case DOWN:
            next_row = row + 1;
            next_col = col;
            return;
        case LEFT:
            next_row = row;
            next_col = col - 1;
            return;
        case RIGHT:
            next_row = row;
            next_col = col + 1;
            return;
        }

    }

    void turn() {
        switch(dir) {
        case UP:
            dir = RIGHT;
            break;
        case DOWN:
            dir = LEFT;
            break;
        case LEFT:
            dir = UP;
            break;
        case RIGHT:
            dir = DOWN;
            break;
        }
    }
};


int main() {

    ifstream myFile("input6.txt");
    string input_line;
    Coord guard;


    // Get input array
    vector< vector<char> > tiles;
    while (getline(myFile, input_line)) {

        vector<char> tile_line;

        for (char c : input_line) {

            if (c == '^') { // Guard starting position
                guard.row = tiles.size();
                guard.col = tile_line.size();
                guard.dir = UP;
                tile_line.push_back('X');
            }
            else {
                tile_line.push_back(c);
            }

        }

        tiles.push_back(tile_line);
    }

    int num_rows = tiles.size();
    int num_cols = tiles[0].size();

    int distinct_positions = 1; // Includes starting position

    int row;
    int col;
    guard.next_coord(row, col);

    int iter = 100;

    while (row >= 0 && col >= 0 && row < num_rows && col < num_cols) {
        
        char& next_tile = tiles[row][col];
        if (next_tile == '#') {
            guard.turn();
        }
        else {
            assert(next_tile == '.' || next_tile == 'X');

            guard.row = row;
            guard.col = col;
            
            if (next_tile == '.') {
                distinct_positions++;
                next_tile = 'X';
            }
        }

        // cout << guard.row << " " << guard.col << distinct_positions << endl;

        // Just in case
        // if (iter < 0) {
        //     break;
        // }
        // iter--;

        guard.next_coord(row, col);

        // print_tiles(tiles);
    }


    cout << "Distinct positions: " << distinct_positions << endl;


    



    



    return 0;

}
