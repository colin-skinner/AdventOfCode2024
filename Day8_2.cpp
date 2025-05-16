#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

////////////////////////////////////////////////////////////////////////
//                               Classes                              //
////////////////////////////////////////////////////////////////////////

struct Coord {
    int row;
    int col;

    Coord(int row, int col) {
        this->row = row;
        this->col = col;
    }

    Coord(size_t row, size_t col) {
        this->row = row;
        this->col = col;
    }

    bool in_bounds(int num_rows, int num_cols) {
        if (row < 0 || col < 0)
            return false;
        if (row >= num_rows || col >= num_cols)
            return false;

        return true;
    }

    bool operator==(const Coord& rhs) const {
        if (row == rhs.row && col == rhs.col)
            return true;
        return false;
    }
};


////////////////////////////////////////////////////////////////////////
//                              Functions                             //
////////////////////////////////////////////////////////////////////////

void print_vec(vector<char> vec) {
    for (const auto& element : vec) {
        cout << element;
    }
    cout << endl;
}

void print_vec(vector<Coord> vec) {
    for (const auto& element : vec) {
        cout << "(" << element.row << "," << element.col << ") ";
    }
    cout << endl;
}

void print_stacked_vec(vector< vector<char> > vec) {
    for (const auto& element : vec) {
        print_vec(element);
    }
}

void print_frequencies(unordered_map<char, vector<Coord>> frequencies) {
    for (auto it = frequencies.begin(); it != frequencies.end(); it++) {
        cout << it->first << ":";
        for (const auto& element : it->second) {
            cout << " (" << element.row << "," << element.col << ")";
        }
        cout << endl;
    }
}

void node_additions(Coord c1, Coord c2, vector<Coord>& coords, int num_rows, int num_cols) {
    coords.clear();
    coords.push_back(c1);
    coords.push_back(c2);

    auto row_diff = c2.row - c1.row;
    auto col_diff = c2.col - c1.col;

    int multiple = 0;

    Coord a(c2.row + row_diff, c2.col + col_diff);
    Coord b(c1.row - row_diff, c1.col - col_diff);

    while (a.in_bounds(num_rows, num_cols)) {
        coords.push_back(a);
        a.row += row_diff;
        a.col += col_diff;
    }

    while (b.in_bounds(num_rows, num_cols)) {
        coords.push_back(b);
        b.row -= row_diff;
        b.col -= col_diff;
    }



} 

////////////////////////////////////////////////////////////////////////
//                               Main                                 //
////////////////////////////////////////////////////////////////////////

int main() {

    ifstream myFile("input8.txt");
    string curr_line;

    vector<vector<char>> grid;

    unordered_map<char, vector<Coord>> frequencies;

    // Importing
    while(getline(myFile, curr_line)) {
        vector<char> curr_row;

        for (auto c : curr_line) {

            // Add coordinate to map
            if (c != '.') {
                Coord coord{grid.size(), curr_row.size()};
                
                if (frequencies.find(c) == frequencies.end()) {
                    vector<Coord> frequency_coords;
                    frequency_coords.push_back(coord);
                    frequencies[c] = frequency_coords;
                }
                else {
                    frequencies[c].push_back(coord);
                }
            }
            curr_row.push_back(c);
        }
        grid.push_back(curr_row);
    }

    int num_rows = grid.size();
    int num_cols = grid[0].size();

    // print_stacked_vec(grid);
    // print_frequencies(frequencies);

    // Adding coordinates to hash map
    vector<Coord> all_antinodes;

    for (auto freq_iter = frequencies.begin(); freq_iter != frequencies.end(); freq_iter++) {
        
        vector<Coord> coords = freq_iter->second;
        vector<Coord> possible_antinodes;

        if (coords.size() < 2) {
            continue;
        }
        
        // print_vec(coords);

        for (int i = 0; i < coords.size(); i++) {
            for (int j = i+1; j < coords.size(); j++) {
                // cout << "Coords: (" << coords[i].row << "," << coords[i].col << ") ";
                // cout << "(" << coords[j].row << "," << coords[j].col << ") " << endl;
                

                node_additions(coords[i], coords[j], possible_antinodes, num_rows, num_cols);
                for (const auto& coord : possible_antinodes) {

                    if (grid[coord.row][coord.col] == '.')
                        grid[coord.row][coord.col] = '#';
                    else {
                        grid[coord.row][coord.col] = '%';
                    }

                    
                    if (find(all_antinodes.begin(), all_antinodes.end(), coord) == all_antinodes.end()) {
                        all_antinodes.push_back(coord);
                        // cout << "(" << coord.row << "," << coord.col << ") ";
                    }
                    // cout << endl;
                }
                // print_stacked_vec(grid); cout << endl;

            }
            
        }
        
    }

    cout << all_antinodes.size() << endl;
    // print_vec(all_antinodes);
    // print_stacked_vec(grid);
    



    return 0;
}