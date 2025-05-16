#include <vector>
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


