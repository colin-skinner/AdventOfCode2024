#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

template <typename T>
void print_vec(vector<T> vec) {
    for (auto element : vec) {
        cout << element << " ";
    }
    cout << endl;
}


vector<long> operate(vector<long> vec, string operation) {

    vector<long> result;
    if (vec.size() == 1) {
        return vec;
    }

    if (operation == "add") {
        vec[1] += vec[0];
        vec.erase(vec.begin());
        return vec;
    }

    else if (operation == "multiply") {
        vec[1] *= vec[0];
        vec.erase(vec.begin());
        return vec;
    }
    else if (operation == "concatenate") {
        vec[1] = stol(to_string(vec[0]) + to_string(vec[1]));
        vec.erase(vec.begin());
        return vec;
    }

    assert(0);
}

bool can_calc(long val, vector<long> operands) {

    // Base case
    if (operands.size() == 1) {
        if (operands[0] == val) {
            return true;
        }
        return false;
    }

    return can_calc(val, operate(operands, "add"))
    || can_calc(val, operate(operands, "multiply"))
    || can_calc(val, operate(operands, "concatenate"));
}

int main() {

    ifstream myFile("input7.txt");
    string curr_line;

    vector<long> results;
    vector< vector<long> > operands;

    // Getting operands and results
    while(getline(myFile, curr_line)) {
        int colon_pos = curr_line.find(":");
        auto curr_result = stol(curr_line.substr(0,colon_pos));
        results.push_back(curr_result);

        vector<long> curr_operands;
        stringstream ss(curr_line.substr(colon_pos + 2));
        int curr_operand;

        while (ss >> curr_operand) {
            curr_operands.push_back(curr_operand);
            
        }

        operands.push_back(curr_operands);
    }

    long total_sum = 0;
    for (int i = 0; i < results.size(); i++) {
        if (can_calc(results[i], operands[i])) {
            total_sum += results[i];
            cout << i << " out of " << results.size() << endl;
        }
    }

    cout << "Sum of results: " << total_sum << endl;
    


    

    return 0;
}