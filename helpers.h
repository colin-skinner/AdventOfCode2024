#include <vector>
#include <list>
#include <unordered_map>
#include <iostream>
#include <string>

template <typename T>
void print_vec(std::vector<T> vec, std::string delim = "") {
    for (const auto& element : vec) {
        std::cout << element << delim;
    }
    std::cout << std::endl;
}

template <typename T>
void print_2D_vec(std::vector<T> vec, std::string delim = "") {
    for (const auto& element : vec) {
        print_vec(element, delim);
    }
    // std::cout << std::endl;
}

template <typename T>
void print_list(std::list<T> li, std::string delim = "") {
    for (const auto& element : li) {
        std::cout << element << delim;
    }
    std::cout << std::endl;
}

template <typename T, typename S>
void print_hash_map(std::unordered_map<T, S> li, std::string delim = "") {
    for (const auto& [key, val] : li) {
        std::cout << key << " " << val << delim;
    }
    std::cout << std::endl;
}



