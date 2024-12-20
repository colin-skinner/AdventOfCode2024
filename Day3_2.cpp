#include <iostream>
#include <fstream>
#include <string>

#include <vector>

using namespace std;

int main() {

    ifstream myFile("input3.txt");
    string line;
    int first, second;

    int grand_total = 0;

    int index = 0;

    bool activated = true;

    while(getline(myFile, line)) {

        while (line.find("mul(") != string::npos) {

            // Do and Don't
            if (line.substr(0,7) == "don't()") {
                activated = false;
                line = line.substr(7);
                continue;
            }

            if (line.substr(0,4) == "do()") {
                activated = true;
                line = line.substr(4);
                continue;
            }
            

            // Finds "mul(" to start a command
            
            if(line.substr(0,4) != "mul(") {
                line = line.substr(1);
                continue;
            }

            line = line.substr(4);

            // Finds next number using ","
            int comma_pos = line.substr(0,4).find(',');
            if (comma_pos != string::npos) {
                first = stoi(line.substr(0,comma_pos));
            }
            else {
                continue;
            }

            line = line.substr(comma_pos + 1);

            int closing_pos = line.substr(0,4).find(')');
            if (closing_pos != string::npos) {
                second = stoi(line.substr(0,closing_pos));
            }
            else {
                continue;
            }

            line = line.substr(closing_pos + 1);
            
            if (activated) {
                // cout << first << " " << second << " " << first * second << endl;
                grand_total += first * second;
            }

            
            // break;
        }

        index++;
    }

    cout << grand_total << endl;


    return 0;
}