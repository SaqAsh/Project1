#include "Countries.h"
#include <iostream>
#include <fstream>
#include <sstream>

Countries::Countries() {
    country_array = new Country*[512];  
    total_countries = 0;
}

Countries::~Countries() {
    for (int i = 0; i < total_countries; i++) {
        delete country_array[i];  
    }
    delete[] country_array;  
}

void Countries::LOAD(std::string filename) {
    std::ifstream file(filename);
    total_countries = 0;
    std::string line, curr, prev;
    bool flag = true;
    while (std::getline(file, line)) {
        std::stringstream s_stream(line);
        std::getline(s_stream, curr, ',');  
        
        if (flag || curr != prev) {
            country_array[total_countries] = new Country();
            country_array[total_countries]->LOAD(curr, filename);
            total_countries++;
            prev = curr;
            flag = false;
        }
    }
    file.close();
    std::cout << "success"<<std::endl;
}

void Countries::LIST(std::string country_name) {
    for(int i = 0; i < total_countries; i++) {
        if (country_array[i]->country_name == country_name) {
            country_array[i]->LIST();
            return;
        }
    }
}

void Countries::RANGE(std::string series_code) {
    std::cout << "RANGE function not implemented yet" << std::endl;
}

void Countries::BUILD(std::string series_code) {
    std::cout << "BUILD function not implemented yet" << std::endl;
}

void Countries::FIND(std::string mean, std::string operation) {
    std::cout << "FIND function not implemented yet" << std::endl;
}

void Countries::DELETE(std::string country_name) {
    std::cout << "DELETE function not implemented yet" << std::endl;
}

void Countries::LIMITS(std::string condition) {
    std::cout << "LIMITS function not implemented yet" << std::endl;
}
