#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "helpers.h"

using namespace std;

struct Coord {
    int row;
    int col;

    Coord(int row, int col) {
        this->row = row;
        this->col = col;
    }

    bool operator=(const Coord& rhs) const {
        return row==rhs.row && col==rhs.col;
    }

    bool operator<(const Coord& rhs) const {
        if (row !=rhs.row) {
            return row < rhs.row;
        }
        return col < rhs.col;
        // else 
        //     return col < rhs.col;
    }
};

struct TrailMap {
    vector<vector<char>> grid;
    int num_rows;
    int num_cols;
};


void print_vec(vector<Coord> vec) {
    for (const auto& element : vec) {
        cout << "(" << element.row << "," << element.col << ") ";
    }
    cout << endl;
}

vector<Coord> advance_trail(TrailMap trail_map, Coord coord, Direction dir) {
    int value = trail_map.grid[coord.row][coord.col] - '0';
    // cout << "(" << coord.row << "," << coord.col << ")" << endl;
    
    switch(dir) {
    case UP:
        if (coord.row <= 0) {
            return vector<Coord>();
        }
        coord.row -= 1;
        break;

    case DOWN:
        if (coord.row >= trail_map.num_rows - 1) {
            return vector<Coord>();
        }
        coord.row += 1;
        break;
    
    case LEFT:
        if (coord.col <= 0) {
            return vector<Coord>();
        }
        coord.col -= 1;
        break;
    case RIGHT:
        if (coord.col >= trail_map.num_cols - 1) {
            return vector<Coord>();
        }
        coord.col += 1;
        break;
    default:
        return vector<Coord>();
    }

    // Must be consecutive
    int next_value = trail_map.grid[coord.row][coord.col] - '0';
    
    if (value + 1 != next_value) {
        return vector<Coord>();
    }

    if (next_value == 9) {
        return vector<Coord>({coord});
    }

    vector<Coord> up_results = advance_trail(trail_map, coord, UP);
    vector<Coord> down_results = advance_trail(trail_map, coord, DOWN);
    vector<Coord> right_results = advance_trail(trail_map, coord, RIGHT);
    vector<Coord> left_results = advance_trail(trail_map, coord, LEFT);

    vector<Coord> results;
    results.insert(results.end(), up_results.begin(), up_results.end());
    results.insert(results.end(), down_results.begin(), down_results.end());
    results.insert(results.end(), right_results.begin(), right_results.end());
    results.insert(results.end(), left_results.begin(), left_results.end());

    return results;
}

vector<Coord> count_trails(TrailMap trail_map, Coord coord) {

    int value = trail_map.grid[coord.row][coord.col] - '0';

    if (value != 0) {
        return vector<Coord>();
    }
        

    vector<Coord> up_results = advance_trail(trail_map, coord, UP);
    // cout << up_results.size() << " ";
    vector<Coord> down_results = advance_trail(trail_map, coord, DOWN);
    // cout << down_results.size() << " ";
    vector<Coord> right_results = advance_trail(trail_map, coord, RIGHT);
    // cout << right_results.size() << " ";
    vector<Coord> left_results = advance_trail(trail_map, coord, LEFT);
    // cout << left_results.size() << " " << endl;

    vector<Coord> results;
    results.insert(results.end(), up_results.begin(), up_results.end());
    results.insert(results.end(), down_results.begin(), down_results.end());
    results.insert(results.end(), right_results.begin(), right_results.end());
    results.insert(results.end(), left_results.begin(), left_results.end());

    // set<Coord> s{results.begin(), results.end()};
    // results = vector<Coord>{s.begin(), s.end()};

    return results;
}

int main() {

    ifstream myFile("input10.txt");
    string file_line;

    TrailMap trail_map;

    while(getline(myFile, file_line)) {
        vector<char> curr_line;
        for (char c : file_line) {
            curr_line.push_back(c);
        }
        trail_map.grid.push_back(curr_line);
    }

    trail_map.num_rows = trail_map.grid.size();
    trail_map.num_cols = trail_map.grid[0].size();
    


    int sum_trails = 0;
    for (int i = 0; i < trail_map.num_rows; i++) {
        for (int j = 0; j < trail_map.num_cols; j++) {
            vector<Coord> result = count_trails(trail_map, Coord(i,j));
            sum_trails += result.size();
        }
    }

    cout << "Result: " << sum_trails << endl;


    return 0;
}