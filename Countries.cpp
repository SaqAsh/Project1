#include "Countries.h"
#include "Node.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Constructor for the countries class, initializes the country array and holds the index of the number of countries we have for ease of adding
// and deleting countries
Countries::Countries() {
    CountryTree = nullptr;
    country_array = new Country*[512];  
    total_countries = 0;
}
//The destructor for the dynamically allocated countries array and the tree
Countries::~Countries() {
    // since the country array is a ** we gotta go through and delete all the individual countries
    for (int i = 0; i < total_countries; i++) {
        delete country_array[i];  
    }
    delete[] country_array;
    // if the country tree exists then delete that
    if (CountryTree) {
        delete CountryTree;
    }
}
// I tried being as efficient as possible, via trying to see if I am at a new country or not and then creating a new country object and then 
// running load on that so that I can save time. 
void Countries::LOAD(std::string filename) {
    std::ifstream file(filename);
    total_countries = 0;
    std::string line, curr, prev;
    //flag is originally true for the first time load is called for a certain country so that we can create a new country object 
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
    std::cout << "success"<< std::endl;
}

// This is the function that handles the listing of the country's statistics based off of the country name
void Countries::LIST(std::string country_name) {
    //linearly searches through the total countries array to find the country name of interest
    for(int i = 0; i < total_countries; i++) {
        if (country_array[i]->country_name == country_name) {
            country_array[i]->LIST(); // calls the list fn from the time series class
            return;
        }
    }
}
// This is the function that outputs the range, this is independent of the tree or anything like that, regardless of the tree we just do this function as is
void Countries::RANGE(std::string series_code) {

    double min_mean = 0.0;
    double max_mean = 0.0;
    // since we aren't able to directly access the first element to vote against we need to set a flag to know when to start the voting algorithm
    bool flag = false; 
    // Goes through all the countries in the countries array and then goes through the linked list of each country to find the series code of interest
    // We are ignoring the empty data sets for this fn to make sure that we don't have a range of zero
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

//This function is the one that calls the build function in the BST class, handles failure cases as well as 
// the dynamic reallocation of a new try if the tree is already built then we need do deal with the old tree
void Countries::BUILD(std::string series_code) {
    if (CountryTree) {
        delete CountryTree;
        CountryTree = nullptr;
    }

    CountryTree = new BST();
    // Goes through all the countries in the countries array and finds the series code of interest
    for (int i = 0; i < total_countries; i++) {
        Node* curr = country_array[i]->linked_list->head;
        while (curr) {
            if (curr->data->series_code == series_code){
                CountryTree->Insert(curr, country_array[i]->country_name);
                break;  // We have found the series, no need to go through the rest of the linked list
            }
            curr = curr->next;
        }
    }
    std::cout << "success" << std::endl;
}

// Is the function that calls the find function in the BST class, handles failure case
void Countries::FIND(double mean, std::string operation) {
    if(!CountryTree){
        std::cout<< "failure" << "\n";
        return;
    }
    CountryTree->find(mean, operation);
}
//This function is the one that calls the delete function in the BST class, handles failure cases
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

//This function is the one that calls the limits function in the BST class, handles failure cases
void Countries::LIMITS(std::string condition) {
    if(!CountryTree){
        std::cout<< "failure" << "\n";
        return;
    }
    CountryTree->Limits(condition);
}
