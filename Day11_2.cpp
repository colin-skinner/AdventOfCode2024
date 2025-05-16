#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

#include <numeric>
#include "helpers.h"

using namespace std;

// True if 2 numbers
bool blink_stone(long long stone, long long& first, long long& second) {
    // 0 to 1
    if (stone == 0) {
        first = 1;
        return false;
    }

    string str = to_string(stone);
    if (str.length() % 2 == 0) {
        long long middle = str.length() / 2;

        first = stoll(str.substr(0,middle));
        second = stoll(str.substr(middle));
        return true;
    }

    first = stone * 2024;

    return false;
}

unordered_map<long long, long> do_stone_thing(const unordered_map<long long, long>& stones) {
    unordered_map<long long, long> resulting_stones;

    for (const auto& [key, val] : stones) {
        long long first;
        long long second;
        bool two_nums = blink_stone(key, first, second);

        // Add first
        if (resulting_stones.find(first) == resulting_stones.end()) {
            resulting_stones[first] = val;
        }
        else {
            resulting_stones[first] += val;
        }

        if (two_nums) {
            if (resulting_stones.find(second) == resulting_stones.end()) {
                resulting_stones[second] = val;
            }
            else {
                resulting_stones[second] += val;
            }
        }

    }

    return resulting_stones;
    

}

int main() {

    ifstream myFile("input11.txt");
    string file_line;

    unordered_map<long long, long> stones;

    while(getline(myFile, file_line)) {

        stringstream line(file_line);
        long long num;
        while (line >> num) {
            if (stones.find(num) == stones.end()) {
                stones[num] = 1;
            }
            else {
                stones[num]++;
            }
            
        }
    }

    
    print_hash_map(stones, ", ");

    int iterations = 75;
    for (int i = 0; i < iterations; i++){
        stones = do_stone_thing(stones);
        
        // print_hash_map(stones, ", ");
    }

    long long total = 0;

    for (const auto& [key, val] : stones){
        total += val;
    }

    cout << "Number of stones: " << total << endl;

    return 0;
}
