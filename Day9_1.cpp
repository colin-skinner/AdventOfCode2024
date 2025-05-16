#include <iostream>
#include <fstream>
#include <string>
#include "helpers.h"

using namespace std;

int main() {

    ifstream myFile("input9.txt");
    string line;
    getline(myFile, line);

    vector<int> blocks;
    int data_len = 0;
    int id = 0;

    for (int index = 0; index < line.size(); index++) {

        int num = line[index] - '0';

        // Adding a file
        if (index % 2 == 0) {
            data_len += num;
            for (int i = 0; i < num; i++) {
                blocks.push_back(id);
            }
            id++;
        }
        else {
            for (int i = 0; i < num; i++) {
                blocks.push_back(-1);
            }
        }
    }

    // print_vec(blocks, " ");
    // cout << data_len << endl;

    // Strip off '.' at the end
    while(blocks.back() == -1) {
        blocks.pop_back();
    }

    // Algorithm
    auto first_free_space = find(blocks.begin(), blocks.end(), -1);
    while(first_free_space != blocks.end() && first_free_space - blocks.begin() <= data_len) {
        // cout << "Dist: " << first_free_space - blocks.begin() << endl;
        swap(*first_free_space, blocks.back());
        blocks.pop_back();
        first_free_space = find(blocks.begin(), blocks.end(), -1);
        // print_vec(blocks, " ");

    }
    cout << "Ending:\t\t";
    print_vec(blocks);

    long checksum = 0;

    for (int i = 0; i < blocks.size(); i++) {
        checksum += i * blocks[i];
    }

    cout << "Checksum: " << checksum << endl;
    

}