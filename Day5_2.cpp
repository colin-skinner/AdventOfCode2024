#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

void print_vec(vector<string> vec) {
    for (auto element : vec) {
        cout << element << " ";
    }
    cout << endl;
}

void print_pair(pair<string, string> p) {
    cout << p.first << " " << p.second << endl;
}

void print_stacked_vec(vector< vector<string> > vec) {
    for (auto element : vec) {
        print_vec(element);
    }
}

void print_pair_vec(vector< pair<string, string> > vec) {
    for (auto element : vec) {
        print_pair(element);
    }
}

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

            // cout << first << " " << second << endl;
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

    // print_stacked_vec(page_orders);

    // return 0;


    // Finding invalid rows
    vector< vector<string> > invalid_orders;
    vector< pair<string, string> > invalid_rules; 

    for (auto order : page_orders) {
        
        bool valid = true;
        
        for (const auto& rule : rules) {
            
            auto first_iter = find(order.begin(), order.end(), rule.first);
            auto second_iter = find(order.begin(), order.end(), rule.second);

            // Both pages must be present
            if (first_iter == order.end() || second_iter == order.end()) {
                continue;
            }

            // cout << first_iter - order.begin() << " " <<  second_iter - order.begin() << endl;
            // cout << first_iter - second_iter << endl;

            // If first page is found after the second page (this is not correct)
            if ((first_iter - second_iter) > 0) {
                invalid_orders.push_back(order);
                invalid_rules.push_back(rule);
                break;
            }

        }
    }

    // Correct invalid orders

    // cout << invalid_orders.size() << endl;
    // cout << invalid_rules.size() << endl;

    for (auto& order : invalid_orders) {
        vector<string> new_row;
        vector< pair<string, string> > new_row_rules;

        // Rules that are in the invalid order
        for (const auto& rule : rules) {
            
            auto first_iter = find(order.begin(), order.end(), rule.first);
            auto second_iter = find(order.begin(), order.end(), rule.second);

            // Both pages must be present
            if (first_iter == order.end() || second_iter == order.end()) {
                continue;
            }

            new_row_rules.push_back(rule);
        }

        auto rule_iter = new_row_rules.begin();

        // Algorithm to make the row from scratch
        while (rule_iter != new_row_rules.end()) {

            auto rule = *rule_iter;
            auto first_iter = find(new_row.begin(), new_row.end(), rule.first);
            auto second_iter = find(new_row.begin(), new_row.end(), rule.second);   
            
            // Add first iter to beginning if it doesn't exist
            if (first_iter == new_row.end()) {
                new_row.insert(new_row.begin(), rule.first);
            }
            // Add second iter to end if it doesn't exist
            if (second_iter == new_row.end()) {
                new_row.push_back(rule.second);
            }

            // If invalid, swap order and go back to beginning
            if ((first_iter - second_iter) > 0) {
                std::swap(*first_iter, *second_iter);
                rule_iter = new_row_rules.begin();
            }
            else {
                rule_iter++;
            }
            
        }

        order = new_row;

        int center_index = (new_row.size() - 1) / 2; // Assumes odd number of things

        int center_val = stoi(new_row.at(center_index));

        page_sum += center_val;


    }

    cout << page_sum << endl;
    return 0;
}