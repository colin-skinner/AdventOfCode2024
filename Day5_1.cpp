#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main() {

    ifstream myFile("input5.txt");
    string line;
    string first, second;

    vector<pair<string,string> > rules;

    vector<vector<string>> page_orders;

    int page_sum = 0;

    while(getline(myFile, line)) {

        // Parsing page orders
        int delimeter_pos = line.find('|');
        if (delimeter_pos != string::npos) {
            first = line.substr(0, delimeter_pos);
            second = line.substr(delimeter_pos+1);

            cout << first << " " << second << endl;
            rules.push_back( {first, second} );
        }


        // Getting page orders
        int is_page_order_line = (line.find(',') != string::npos);
        if (is_page_order_line) {

            stringstream csv_line(line);

            vector<string> page_order;
            string value;
            while(getline(csv_line, value, ',')) {
                page_order.push_back(value);
            }

            page_orders.push_back(page_order);   
        } 
    }

    cout << endl;


    // Finding valid rows
    vector<vector<string> > valid_orders;

    for (auto order : page_orders) {
        
        bool valid = true;
        
        for (const auto& [first_page, second_page] : rules) {
            
            auto first_iter = find(order.begin(), order.end(), first_page);
            auto second_iter = find(order.begin(), order.end(), second_page);

            // Both pages must be present
            if (first_iter == order.end() || second_iter == order.end()) {
                continue;
            }

            // cout << first_iter - order.begin() << " " <<  second_iter - order.begin() << endl;
            // cout << first_iter - second_iter << endl;

            // If first page is found after the second page (this is not correct)
            if ((first_iter - second_iter) > 0) {
                // cout << "BAD" << endl;
                valid = false;
                break;
            }
        }

        // Valid if nothing fails
        if (valid)
            valid_orders.push_back(order);

        // cout << "-------" << endl;
    }

    // Adding middle values

    for (auto order : valid_orders) {
        int center_index = (order.size() - 1) / 2; // Assumes odd number of things

        int center_val = stoi(order.at(center_index));

        page_sum += center_val;
    }




    // for (auto order : valid_orders) {
    //     for (auto page : order) {
    //         cout << page << " ";
    //     }
    //     cout << endl;
    // }

    

    

    cout << page_sum << endl;




    return 0;
}