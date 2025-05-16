#include <iostream>
#include <fstream>
#include <string>
#include "helpers.h"

using namespace std;

template <typename T>
void print_files(vector<T> vec, std::string delim = "") {
    for (const auto& element : vec) {
        if (element == -1) {
            cout << '.' << delim;
        }
        else {
            cout << element << delim;
        }
    }
    cout << std::endl;
}



int main() {

    ifstream myFile("input9.txt");
    string line;
    getline(myFile, line);

    vector<int> blocks;
    vector<int> block_sizes;
    int data_len = 0;
    int id = 0;

    for (int index = 0; index < line.size(); index++) {

        int num = line[index] - '0';
        
        // Adding a file
        if (index % 2 == 0) {
            data_len += num;
            for (int i = 0; i < num; i++) {
                blocks.push_back(id);
                block_sizes.push_back(num);
            }
            id++;
        }
        else {
            for (int i = 0; i < num; i++) {
                blocks.push_back(-1);
                block_sizes.push_back(num);
            }
        }
    }
    // print_files(blocks);
    // print_files(block_sizes);

    // Algorithm
    int insertion_index = 0;
    int file_index = blocks.size()-1;

    while(file_index >= 0) {
        // insertion_index = find(blocks.begin(), blocks.end(), -1) - blocks.begin();
        insertion_index = 0;

        // Must be at a file to try and insert
        if (blocks[file_index] == -1) {
            file_index--;
            continue;
        }

        // Finds index to insert
        for (; insertion_index < file_index; insertion_index++) {
            if (blocks[insertion_index] == -1 && block_sizes[insertion_index] >= block_sizes[file_index])
                break;
        }
        if (insertion_index >= file_index) {
            file_index -= block_sizes[file_index];
            continue;
        }
        // print_files(blocks);
        // print_files(block_sizes);
        // cout << "Inserting at index: " << insertion_index << " with " << blocks[insertion_index] << " with size " << block_sizes[insertion_index] << endl; // DEBUG
        // cout << "File at index: " << file_index << " with " << blocks[file_index] << " with size " << block_sizes[file_index] << endl;

        // cout << block_sizes[insertion_index] << endl;
        // cout << block_sizes[file_index] << endl << endl; // DEBUG

        int empty_space_size = block_sizes[insertion_index];
        int file_size = block_sizes[file_index];

        // Swaps file with empty space and corrects empty space file size
        for (int i = 0; i < empty_space_size; i++) {

            // If this is the part of empty space to swap
            if (i < file_size) {
                // cout << "A" << endl;
                swap(blocks[insertion_index + i], blocks[file_index - i]);
                swap(block_sizes[insertion_index + i], block_sizes[file_index - i]);
                // print_files(blocks);
            }
            else {
                block_sizes[insertion_index + i] = empty_space_size - file_size;
            }
            // cout << "HMM" << endl;
        }

        // file_index -= block_sizes[file_index];
        // while (!can_insert && insertion_index < file_index) {
        //     if (blocks[insertion_index] != -1) { // If not an empty space, advance
        //         insertion_index += block_sizes[insertion_index];
        //         continue;
        //     }
        //     if (block_sizes[insertion_index] < block_sizes[file_index]) { // If not a large enough space, advance
        //         insertion_index += block_sizes[insertion_index];
        //         continue;
        //     }
        //     break;
        // }

        // If insertion index is too far, then moves by the file block amount (cannot insert)

        // while ( // Cannot insert
        // && blocks[insertion_index] != -1)

        


        // cout << insertion_index << endl;
        // cout << file_index << endl << endl;

        // cout << blocks[insertion_index] << endl;
        // cout << blocks[file_index] << endl << endl;

        // cout << block_sizes[insertion_index] << endl;
        // cout << block_sizes[file_index] << endl << endl;


    }

    cout << "Ending:\t\t";
    print_vec(blocks);

    long checksum = 0;

    for (int i = 0; i < blocks.size(); i++) {
        if (blocks[i] != -1)
            checksum += i * blocks[i];
    }

    cout << "Checksum: " << checksum << endl;
    

}



    // auto first_free_space = find(blocks.begin(), blocks.end(), -1);
    // int index = first_free_space - blocks.begin();
    // int free_space_instance = 0;

    // cout << index << endl;
    // cout << block_sizes[index] << endl;
    // cout << block_sizes.back() << endl;

    // while(first_free_space != blocks.end() // '.' not at the end (it exists)
    // && index <= data_len) {// '.' not past all data

        
    //     cout << "Dist: " << first_free_space - blocks.begin() << endl;

    //     block_sizes[index] >= block_sizes.back()

    //     // Have to change block sizes of all "empty spaces"
    //     for (int i = 0; i < block_sizes[index]; i++) {

    //         // If this is the part of empty space to swap
    //         if (i < block_sizes.back()) {
    //             swap(blocks[index + i], blocks.back());
    //             swap(block_sizes[index + i], block_sizes.back());
    //             blocks.pop_back();
    //             block_sizes.pop_back();
    //         }
    //         else {
    //             block_sizes[i] = block_sizes[i] - block_sizes.back();
    //         }
    //         // cout << "HMM" << endl;
    //     }

        
    //     first_free_space = find(blocks.begin(), blocks.end(), -1);
    //     index = first_free_space - blocks.begin();
    //     print_vec(blocks, " ");

    // }


// 00992111777.44.333....5555.6666.....8888..