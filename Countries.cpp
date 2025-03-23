#include "Countries.h"
#include "Node.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Constructor for the countries class, initializes the country array and holds the index of the number of countries we have for ease of adding
// and deleting countries
Countries::Countries() {
    CountryTree = nullptr;
    country_array = new Country*[512]();  
    total_countries = 0;
}
//The destructor for the dynamically allocated countries array and the tree
Countries::~Countries() {
    // since the country array is a ** we gotta go through and delete all the individual countries
    for (int i = 0; i < 512; i++) {
        delete country_array[i];  
    }
    delete[] country_array;
    // if the country tree exists then delete that
    if (CountryTree) delete CountryTree;
    
}

//This is the function that handles the lookup of a country in the hash table
void Countries::LOOKUP(std::string country_code) {
    int i = 0;
    if (!countryExists(country_code)) {
        std::cout << "failure" << "\n";
        return;
    }
    int index = overall_hash_delete(country_code, i);
    std::cout << "index " << index << " searches " << i + 1 << "\n";
}

//this is the function that handles the removal of a country from the hash table
void Countries::REMOVE(std::string country_code){
    int i = 0; 
    bool isInsideTable = countryExists(country_code);
    // if the country is not in the table then we can't remove it
    if(!isInsideTable){
        std::cout << "failure" << "\n";
        return;
    }
    //call the delete helper for deletion 
    int index = overall_hash_delete(country_code, i);
    Country* country = country_array[index];
    //if somehow the country is already removed then we can't remove it again
    //signified via po
    if(country->country_name == "po"){
        std::cout << "failure" << "\n";
        return;
    }
    //we gotta also remove it from the tree 
    if(CountryTree) CountryTree->deleteFn(country->country_name);
    
    //delete the country and then mark it as removed using po, also known as previously occupied 
    country->country_name = "po"; // mark as removed, also known as previously occupied as per the project docs
    country->country_code = "po";
    std::cout << "success" << "\n";
}

//This is the function that handles the addition of a country to the hash table
void Countries::INSERT(std::string country_code, std::string file_name) {
    std::ifstream file(file_name);
    std::string line, country_code_from_file, country_name;
    int i = 0;
    int index = overall_hash_insert(country_code, i);
    int isInsideTable = countryExists(country_code);
    // if the country is already in the table then we can't insert it again
    if (isInsideTable) {
        std::cout << "failure" << "\n";
        file.close();
        return;
    }

    //general file reading and checking if the country code is in the file or not using get line
    while (std::getline(file, line)) {
        std::stringstream s_stream(line);
        std::getline(s_stream, country_name, ','); 
        std::getline(s_stream, country_code_from_file, ',');  
        
        if (country_code_from_file == country_code) {
            //if there is an object present in the place we are tryna insert then we delete it to make sure there
            //is no mem leak
            if (country_array[index] != nullptr) delete country_array[index];  
            //standard insertion
            Country* country = new Country();
            country->LOAD(country_name, file_name);
            country_array[index] = country;

            std::cout << "success" << "\n";
            file.close();
            return;
        }
    }
}

/*
    CITATION: 

    A small part of this function was generated with the help of chat.openai.com with the prompt 
    give me a less than one sentence answer, as minimal as possible because I don't got time, make sure ur correct 
    what is the ascii value of capital A, where chat responded with 65 which is what I am using in this function
    
*/
//simple the computation of the H1
int Countries::primary_hash(std::string country_code) {
    return ((country_code[0] - 65) * 26 * 26 + (country_code[1] - 65) * 26 + (country_code[2] - 65)) % 512;
}

/*
    CITATION: 

    A small part of this function was generated with the help of chat.openai.com with the prompt 
    give me a less than one sentence answer, as minimal as possible because I don't got time, make sure ur correct 
    what is the ascii value of capital A, where chat responded with 65 which is what I am using in this function
    
*/
//simply the computation of the H2
int Countries::secondary_hash(std::string country_code) {
    int temp = (((country_code[0] - 65) * 26 * 26 + (country_code[1] - 65) * 26 + (country_code[2] - 65))/ 512) % 512;
    return temp % 2 == 0 ? temp + 1 : temp;
}

//This is the helper function that lets me see if the country exists in the table or not
bool Countries::countryExists(std::string country_code) {
    int H1 = primary_hash(country_code);
    int H2 = secondary_hash(country_code);
    int index{0};
    int i = 0;
    //hashing and seeing if the country code is in the table or not
    while(i < 512) {  
        index = (H1 + i * H2) % 512;
        if (country_array[index] == nullptr) return false;
        if (country_array[index]->country_code == country_code) return true;
        ++i;
    }

    return false;
}

// This function is the one that handles the insertion of the country into the hash table
// It allows me to know if the country is in the table or if there is a previous occupation of that spot through the po 
int Countries::overall_hash_insert(std::string country_code, int& i){    
    int H1 = primary_hash(country_code);
    int H2 = secondary_hash(country_code);
    int index = 0;
    i = 0;
    while(1){
        index = (H1 + i * H2) % 512;
        if(country_array[index] == nullptr || country_array[index]->country_code == "po") return index;
        ++i;
    }
    
    return -1;
}
// This function is the one that handles the deletion of the country from the hash table
// It allows me to know if the country is in the table or not and then returns the index of the country in the table
int Countries::overall_hash_delete(std::string country_code, int& i){    
    int H1 = primary_hash(country_code);
    int H2 = secondary_hash(country_code);
    int index{0};
    i = 0;
    while(1){
        index = (H1 + i * H2) % 512;
        if(country_array[index] != nullptr && country_array[index] -> country_code == country_code) return index;
        if(country_array[index] == nullptr) return -1; 
        ++i;
    }
    return -69;
}

// I tried being as efficient as possible, via trying to see if I am at a new country or not and then creating a new country object and then 
// running load on that so that I can save time. 
void Countries::LOAD(std::string filename) {
    std::ifstream file(filename);
    int i = 0;
    total_countries = 0;
    std::string line, curr, prev;
    //flag is originally true for the first time load is called for a certain country so that we can create a new country object 
    bool flag = true;
    while (std::getline(file, line)) {
        std::stringstream s_stream(line);
        std::getline(s_stream, curr, ',');  
        if (flag || curr != prev) {
            Country* country = new Country();
            country->LOAD(curr, filename);
            country_array[overall_hash_insert(country->country_code, i)] = country;
            total_countries++;
            prev = curr;
            flag = false;
        }
    }
    file.close();
    std::cout << "success"<< "\n";
}

// This is the function that handles the listing of the country's statistics based off of the country name
void Countries::LIST(std::string country_name) {
    //linearly searches through the total countries array to find the country name of interest
    for(int i = 0; i < 512; i++) {
        if (country_array[i] == nullptr) continue;
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
    for (int i = 0; i < 512; i++) {
        if(country_array[i] == nullptr) continue;
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
    std::cout << min_mean << " " << max_mean << "\n";
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
    for (int i = 0; i < 512; i++) {
        if(country_array[i] == nullptr) continue;
        Node* curr = country_array[i]->linked_list->head;
        while (curr) {
            if (curr->data->series_code == series_code){
                CountryTree->Insert(curr, country_array[i]->country_name);
                break;  // We have found the series, no need to go through the rest of the linked list
            }
            curr = curr->next;
        }
    }
    std::cout << "success" << "\n";
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
