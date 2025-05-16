#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <numeric>
#include "helpers.h"

using namespace std;

vector<long long> do_stone_thing(vector<long long> stones) {
    vector<long long> result;
    
    for (long long i : stones) {
        
        // 0 to 1
        if (i == 0) {
            result.push_back(1);
            continue;
        }

        // Replaced by 2 stones
        string str = to_string(i);
        if (str.length() % 2 == 0) {
            long long middle = str.length() / 2;
            result.push_back(stoi(str.substr(0,middle)));
            result.push_back(stoi(str.substr(middle)));
            continue;
        }

        result.push_back(i * 2024);
    }

    return result;
}

int main() {

    ifstream myFile("input11.txt");
    string file_line;

    vector<long long> stones;

    while(getline(myFile, file_line)) {

        stringstream line(file_line);
        long long num;
        while (line >> num) {
            stones.push_back(num);
        }

    }

    
    print_vec(stones, " ");

    int iterations = 25;
    for (int i = 0; i < iterations; i++){
        cout << i << endl;
        stones = do_stone_thing(stones);
        
        // print_vec(stones, " ");
    }

    cout << "Number of stones: " << stones.size() << endl;


    return 0;
}