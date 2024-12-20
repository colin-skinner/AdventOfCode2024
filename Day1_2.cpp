#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <vector>
#include <algorithm>

using namespace std;

int main() {

    ifstream myFile("input1.txt");
    string raw_line;
    int first, second;

    vector<int> first_values;
    vector<int> second_values;

    

    long long total_distance = 0;

    int index = 0;

    while(getline(myFile, raw_line)) {

        stringstream line(raw_line);
        line >> first >> second;

        first_values.push_back(first);
        second_values.push_back(second);

        index++;
    }

    std::sort(first_values.begin(), first_values.end());
    // std::sort(second_values.begin(), second_values.end());

    
    for (size_t i = 0; i < first_values.size(); i++) {
        int number = first_values[i];
        
        int count = std::count(second_values.begin(), second_values.end(), number);

        // cout << left_place << " " << right_place << endl;
        total_distance += number * count;
        // cout << abs(left_place - right_place) << endl;
    }

    

    cout << total_distance << endl;

    return 0;
}