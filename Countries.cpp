#include "Countries.h"
#include "Node.h"
#include <iostream>
#include <fstream>
#include <sstream>

Countries::Countries() {
    CountryTree = nullptr;
    country_array = new Country*[512];  
    total_countries = 0;
}

Countries::~Countries() {
    for (int i = 0; i < total_countries; i++) {
        delete country_array[i];  
    }
    delete[] country_array;  
    if (CountryTree) {
        delete CountryTree;
    }
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

    double min_mean = 0.0;
    double max_mean = 0.0;
    bool flag = false;

    for (int i = 0; i < total_countries; i++) {
        Node* curr = country_array[i]->linked_list->head;
        while (curr != nullptr) {
            if (curr->data->series_code == series_code && !curr->data->emptyDataSet()) {
                double mean = curr->data->mean();
                if (!flag) {
                    min_mean = mean;
                    max_mean = mean;
                    flag = true;
                } else {
                    if (mean < min_mean)
                        min_mean = mean;
                    if (mean > max_mean)
                        max_mean = mean;
                }
                break;  
            }
            curr = curr->next;
        }
    }
    std::cout << min_mean << " " << max_mean << std::endl;
}


void Countries::BUILD(std::string series_code) {
    if (CountryTree) {
        delete CountryTree;
        CountryTree = nullptr;
    }

    CountryTree = new BST();

    for (int i = 0; i < total_countries; i++) {
        Node* curr = country_array[i]->linked_list->head;
        std::string countryName = country_array[i]->country_name;
        while (curr) {
            if (curr->data->series_code == series_code){
                CountryTree->Insert(curr, countryName);
                break;  
            }
            curr = curr->next;
        }
    }
    std::cout << "success" << std::endl;
}



void Countries::FIND(double mean, std::string operation) {
    if(!CountryTree){
        std::cout<< "failure" << "\n";
        return;
    }
    CountryTree->find(mean, operation);
}

void Countries::DELETE(std::string country_name) {
    if(!CountryTree){
        std::cout<< "failure" << "\n";
        return;
    }
    if(CountryTree->deleteFn(country_name)){
        std::cout<< "success" << "\n";
        return;
    }
    else{
        std::cout<< "failure" << "\n";
        return;
    }
}

void Countries::LIMITS(std::string condition) {
    if(!CountryTree){
        std::cout<< "failure" << "\n";
        return;
    }
    CountryTree->Limits(condition);
}
