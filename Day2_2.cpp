#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <vector>

using namespace std;

#define INCREASING 1
#define DECREASING -1
#define UNSET 0

bool is_safe_row(vector<int> current_row) {


    int direction = UNSET;

    int current = current_row[0];

    for (size_t i = 1; i < current_row.size(); i++) {

        int next = current_row[i];

        // Direction not set
        if (direction == UNSET) {
            if (next > current) {
                direction = INCREASING;
            }
            else if (next < current) {
                direction = DECREASING;
            }
            else {
                return false;
            }

        }

        // Unsafe direction
        else if ((direction == INCREASING && next < current)) {
            return false;
        }
        else if ((direction == DECREASING && next > current)) {
            return false;
        }


        
        int diff = abs(next - current);

        // Unsafe change
        if (diff < 1 || diff > 3) {
            return false;
        }   
        
        current = next;
    }

    return true;
}

int main() {

    ifstream myFile("input2.txt");
    string raw_line;
    int current, next;
    vector<int> current_row;

    int safe_rows = 0;

    int direction;

    while(getline(myFile, raw_line)) {

        stringstream line(raw_line);

        while (line >> current) {
            current_row.push_back(current);
        }
        
        for (size_t i = 0; i < current_row.size(); i++) {
            vector<int> temp = current_row;
            temp.erase(temp.begin() + i);

            if (is_safe_row(temp)) {
                safe_rows++;
                break;
            }
            
        }

        // if (is_safe_row(current_row))
        //     safe_rows++;

        current_row.clear();

    }

    cout << safe_rows << endl;

    return 0;
}