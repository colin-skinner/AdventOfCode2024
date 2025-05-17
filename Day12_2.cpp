#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <map>

#include <numeric>
#include "helpers.h"

using namespace std;



struct Coord {
    int row;
    int col;

    Coord(int row, int col) {
        this->row = row;
        this->col = col;
    }

    bool operator==(const Coord& rhs) const {
        return row==rhs.row && col==rhs.col;
    }

    bool operator<(const Coord& rhs) const {
        if (row !=rhs.row) {
            return row < rhs.row;
        }
        return col < rhs.col;
    }

    friend ostream& operator << (ostream &out, const Coord& c) {
        out << "(" << c.row << "," << c.col << ")";
        return out;
    }
};

// Direction should be UP or LEFT
struct Edge {
    int row;
    int col;
    Direction dir;

    Edge(int row, int col, Direction dir) {
        this->row = row;
        this->col = col;
        this->dir = dir;
    }

    bool operator==(const Edge& rhs) const {
        return row==rhs.row && col==rhs.col && dir==rhs.dir;
    }

    bool operator<(const Edge& rhs) const {
        if (row !=rhs.row) {
            return row < rhs.row;
        }
        else if (col !=rhs.col) {
            return col < rhs.col;
        }
        return dir < rhs.dir;
    }

    friend ostream& operator << (ostream &out, const Edge& e) {
        out << "(" << e.row << "," << e.col << "," << e.dir << ")";
        return out;
    }
};

struct Garden  {
    vector<string> plants;
    vector<string> searched;
    int num_rows;
    int num_cols;

    void create_empty_plot() {
        searched.clear();
        for (string s : plants) {
            string row = "";
            for (char c : s) {
                row += '.';
            }
            searched.push_back(row);
        }
    }

    bool find_uncategorized(Coord& c) {
        for (int row = 0; row < num_rows; row++) {
            size_t loc = searched[row].find('.');
            if (loc != std::string::npos) {
                c.row = row;
                c.col = loc;
                return true;
            }
        }

        return false;
    }
};

struct Region {
    char label;
    set<Coord> plots;
    set<Edge> fences;
    set<set<Edge>> sides;
    int area = 0;
    int perimeter = 0;

    friend ostream& operator << (ostream &out, const Region& r) {
        out << "Region " << r.label << ": ";
        out << r.area << " plots, ";
        out << r.perimeter << " perimeter, ";
        out << r.sides.size() << " sides" << endl;

        return out;
    }
};

set<Coord> find_area_dfs(Coord starting_c, char label, Garden& garden) {

    set<Coord> plot_coords;

    set<Coord> to_search{starting_c};
    set<Coord> searched{};

    while (to_search.size() > 0) {
        
        Coord c = *to_search.begin(); // Take from front of list
        to_search.erase(c); // Remove from to_search list
        searched.insert(c); // Add to searched list
        // cout << "Searching: " << c << endl;

        if (garden.plants[c.row][c.col] != label) { // Continue if not same label or if searched
            continue;
        } 
        plot_coords.insert(c); // Or add to all_coords 

        
        if (c.row > 0) {
            Coord next{c.row-1,c.col};
            if (searched.count(next) == 0)
                to_search.insert(next);
        }
        if (c.col > 0) {
            Coord next{c.row,c.col-1};
            if (searched.count(next) == 0)
                to_search.insert(next);
        }
        if (c.row < garden.num_rows-1) {
            Coord next{c.row+1,c.col};
            if (searched.count(next) == 0)
                to_search.insert(next);
        }
        if (c.col < garden.num_cols-1) {
            Coord next{c.row,c.col+1};
            if (searched.count(next) == 0)
                to_search.insert(next);
        }
    }

    for (Coord c : plot_coords) {
        garden.searched[c.row][c.col] = 'X';
    }

    return plot_coords;
}

void add_edge(map<Edge, int>& all_edges, Edge& e) {
    if (all_edges.contains(e)) {
        all_edges[e]++;
    }
    else {
        all_edges[e] = 1;
    }
}

set<Edge> find_perimeter(Region region) {

    int perimeter = 0;

    map<Edge, int> all_edges;

    for (Coord c : region.plots) {
        
        // For all 4 directions, try to add edge. but if it's in the edges aready, remove it
        // Up
        Edge up_e{c.row, c.col, UP};
        add_edge(all_edges, up_e);
        
        // Left
        Edge left_e{c.row, c.col, LEFT};
        add_edge(all_edges, left_e);

        // Down
        Edge down_e{c.row+1, c.col, UP};
        add_edge(all_edges, down_e);
        
        // Right
        Edge right_e{c.row, c.col+1, LEFT};
        add_edge(all_edges, right_e);
    }

    set<Edge> final_edges;

    for (const auto& [edge, num] : all_edges) {
        if (num == 1) {
            perimeter++;
            final_edges.insert(edge);
            // cout << num << " " << edge.row << " " << edge.col << " " << edge.dir << endl;
        }
    }

    return final_edges;

}

// Assumes that e is a valid horizontal edge with UP direction
set<Edge> find_horizontal(Edge e, Region& region) {

    set<Edge> to_search{e};
    set<Edge> searched;

    bool is_above_region = region.plots.contains(Coord{e.row, e.col});

    set<Edge> result;

    while (to_search.size() > 0) {
        
        Edge c = *to_search.begin(); // Take from front of list
        to_search.erase(c); // Remove from to_search list
        searched.insert(c); // Add to searched list

        // cout << "Searching: " << c << endl;

        if (!region.fences.contains(c)) { // Continue if not in fences
            continue;
        }

        if (is_above_region && !region.plots.contains(Coord{c.row, c.col})) {
            continue;
        }
        if (!is_above_region && !region.plots.contains(Coord{c.row-1, c.col})) {
            continue;
        }

        result.insert(c);
        region.fences.erase(c);
        
        Edge left = {c.row, c.col-1, c.dir};
        if (searched.count(left) == 0) {
            to_search.insert(left);
        }

        Edge right = {c.row, c.col+1, c.dir};
        if (searched.count(right) == 0) {
            to_search.insert(right);
        }
    }

    return result;
}

// Assumes that e is a valid vertical edge with LEFT direction
set<Edge> find_vertical(Edge e, Region& region) {

    set<Edge> to_search{e};
    set<Edge> searched;

    set<Edge> result;

    bool is_left_of_region = region.plots.contains(Coord{e.row, e.col});

    while (to_search.size() > 0) {
        
        Edge c = *to_search.begin(); // Take from front of list
        to_search.erase(c); // Remove from to_search list
        searched.insert(c); // Add to searched list


        if (!region.fences.contains(c)) { // Continue if not in fences
            continue;
        }

        if (is_left_of_region && !region.plots.contains(Coord{c.row, c.col})) {
            continue;
        }
        if (!is_left_of_region && !region.plots.contains(Coord{c.row, c.col-1})) {
            continue;
        }

        result.insert(c);
        region.fences.erase(c);
        
        Edge up = {c.row-1, c.col, c.dir};
        if (searched.count(up) == 0) {
            to_search.insert(up);
        }

        Edge down = {c.row+1, c.col, c.dir};
        if (searched.count(down) == 0) {
            to_search.insert(down);
        }
    }

    return result;
}

set<set<Edge>> sort_sides(Region region) {

    int perimeter = 0;

    set<Edge> unexplored = region.fences;
    set<set<Edge>> sides;

    while (unexplored.size() > 0) {
        Edge edge = *unexplored.begin();
        unexplored.erase(edge);

        if (edge.dir == UP) {

            set<Edge> side = find_horizontal(edge, region);
            if (side.size() > 0)
                sides.insert(side);
        }

        if (edge.dir == LEFT) {

            set<Edge> side = find_vertical(edge, region);
            if (side.size() > 0)
                sides.insert(side);
        }
    }

    // for (auto s : sides) {
    //     print_set(s);
    //     cout << s.size() << endl;
    // }
    // cout << endl;

    return sides;

}

int main() {

    ifstream myFile("input12.txt");
    string file_line;

    Garden garden;
    vector<Coord> unparsed_plots;
    // Loading plants
    while(getline(myFile, file_line)) {
        for (int i = 0; i < file_line.size(); i++) {
            Coord c{int(garden.plants.size()),i};
            unparsed_plots.push_back(c);
        }
        garden.plants.push_back(file_line);
    }

    garden.create_empty_plot();
    garden.num_rows = garden.plants.size();
    garden.num_cols = garden.plants[0].size();


    Coord coord{0,0};
    vector<Region> regions;
    while (garden.find_uncategorized(coord)) {
        Region region;
        region.label = garden.plants[coord.row][coord.col];
        
        set<Coord> coords = find_area_dfs(coord, region.label, garden);
        region.plots = coords;
        region.area = coords.size();

        set<Edge> edges = find_perimeter(region);
        region.fences = edges;
        region.perimeter = edges.size();

        region.sides = sort_sides(region);

        regions.push_back(region);

        cout << region;

        // break;
    }

    long total = 0;
    for (Region r : regions) {
        total += r.area * r.sides.size();
    }

    cout << "Total: " << total << endl;

    
    return 0;
}

