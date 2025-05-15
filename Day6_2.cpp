#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

////////////////////////////////////////////////////////////////////////
//                          Classes and Stuff                         //
////////////////////////////////////////////////////////////////////////

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

void print_vec(vector<char> vec) {
    for (auto element : vec) {
        cout << element;
    }
    cout << endl;
}

void print_vec(vector<Coord> vec) {
    for (auto c : vec) {
        cout << c.row << " " << c.col << endl;
    }
}

void print_tiles(vector< vector<char> > vec) {
    for (auto element : vec) {
        print_vec(element);
    }
    cout << endl;
}

bool is_time_loop(vector< vector<char> > tiles, Coord guard) {

    int num_rows = tiles.size();
    int num_cols = tiles[0].size();

    int row;
    int col;
    guard.next_coord(row, col);

    vector<Coord> coord_hist;
    int similar_count = 0;

    int iter = num_rows * num_cols;

    while (row >= 0 && col >= 0 && row < num_rows && col < num_cols) {
        
        char& next_tile = tiles[row][col];
        if (next_tile == '#') {

            guard.turn();
            
        }
        else {
            assert(next_tile == '.' || next_tile == 'X');
            guard.row = row;
            guard.col = col;
        }

        guard.next_coord(row, col);

        if (iter <= 0) {
            return true;
        }
        iter--;

    }

    return false;
}

////////////////////////////////////////////////////////////////////////
//                                Main                                //
////////////////////////////////////////////////////////////////////////

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

        auto new_board(tiles);

        tiles.push_back(tile_line);
    }

    // Count loops
    int num_rows = tiles.size();
    int num_cols = tiles[0].size();

    int loops = 0;

    for (int row = 0; row < num_rows; row++) {
        for (int col = 0; col < num_cols; col++) {
            auto new_tiles = tiles;
            new_tiles[row][col] = '#';

            // print_tiles(new_tiles);
            // cout << row << " " << col << endl;
            if (is_time_loop(new_tiles, guard)) {
                loops++;
                cout << loops;
            }
        }
    }





    cout << "Distinct loops: " << loops << endl;


    



    



    return 0;

}



////////////////////////////////////////////////////////////////////////
//                        Failed loop detection                       //
////////////////////////////////////////////////////////////////////////



            // if (coord_hist.size() < 4) {
            //     Coord c;
            //     c.row = guard.row;
            //     c.col = guard.col;
            //     coord_hist.push_back(c);
            // }
            // else {
                
            //     Coord front = coord_hist[similar_count];
            //     cout << "-------------" << endl;
            //     cout << similar_count << endl;
            //     cout << front.row << " " << front.col << endl;
            //     cout << guard.row << " " << guard.col << endl;
            //     cout << coord_hist.size() << endl;
            //     print_vec(coord_hist);
                

            //     // If matching, try to match to length of vector
            //     if (front.row == guard.row && front.col == guard.col) {
            //         similar_count++;
            //         cout << "SIMILAR" << endl;
            //         if (similar_count == coord_hist.size()) 
            //             return true;
            //     }
            //     // If it doesn't match, remove until it does, then add to history
            //     else {
            //         similar_count = 0;

            //         while (coord_hist.size() > 0 && front.row == guard.row && front.col == guard.col) {
                    
            //             coord_hist.erase(coord_hist.begin());
            //             front = coord_hist[similar_count];
            //         }
            //         if (coord_hist.size() <= 0) { // Add if empty
            //             Coord c;
            //             c.row = guard.row;
            //             c.col = guard.col;
            //             coord_hist.push_back(c);
            //         }
                    
            //     }
            // }
                