#include <iostream>
#include <string>
#include "TimeSeries.h"
#include "Countries.h"

// This is the function that handles loading data from a file
void handle_load(Countries *countries){
    std::string filename;
    if(std::cin >> filename){
        countries->LOAD(filename);
    }
}

/*
    CITATION: 

    [4] A small part of this function was generated with the help of chat.openai.com with the prompt 
    "I LITERALLY CANT GET THIS TO WORK, WHY DO TWO WORD COUNTRY NAMES NOT WORK IN MY PROGRAM, PLEASE HELP"
    where the model responded with telling me to use std::cin.ignore() which was the solution to the problem.
    This was a very helpful resource since I was not able to figure out the solution to the problem on my own.
*/

// This is the function that handles listing a country's details
void handle_list(Countries *countries){
    std::string countries_name;
    std::cin.ignore();
    if(std::getline(std::cin, countries_name)){
        countries->LIST(countries_name);
    }  
}

// This is the function that handles computing the range of a time series
void handle_range(Countries *countries){
    std::string series_code;
    if(std::cin >> series_code){
        countries->RANGE(series_code);
    }  
}

// This is the function that handles building the binary tree for a time series
void handle_build(Countries *countries){
    std::string countries_name;
    if(std::cin >> countries_name){
        countries->BUILD(countries_name);
    }  
}

// This is the function that handles finding countries based on a mean value
void handle_find(Countries *countries){
    std::string mean;
    std::string operation;
    if(std::cin >> mean >> operation){
        countries->FIND(std::stod(mean), operation);
    }
}

/*
    CITATION: 

    [5] A small part of this function was generated with the help of chat.openai.com with the prompt 
    "I LITERALLY CANT GET THIS TO WORK, WHY DO TWO WORD COUNTRY NAMES NOT WORK IN MY PROGRAM, PLEASE HELP"
    where the model responded with telling me to use std::cin.ignore() which was the solution to the problem.
    This was a very helpful resource since I was not able to figure out the solution to the problem on my own.
*/

// This is the function that handles deleting a country from the binary tree
void handle_delete(Countries *countries){
    std::string countries_name;
    std::cin.ignore();
    if(std::getline(std::cin, countries_name)){
        countries->DELETE(countries_name);
    }
}

// This is the function that handles retrieving the countries with the lowest or highest mean
void handle_limits(Countries *countries){
    std::string condition;
    if(std::cin >> condition){
        countries->LIMITS(condition);
    }
}

//This is the function that handles looking up a country into the hashtable
void handle_lookup(Countries *countries){
    std::string country_code;
    if(std::cin >>country_code){
        countries->LOOKUP(country_code);
    }
}

//this is the function that handles removing a country into the hashtable
void handle_remove(Countries *countries){
    std::string country_code;
    if(std::cin >>country_code){
        countries->REMOVE(country_code);
    }
}

//this is the function that handles inserting a country into the hashtable
void handle_insert(Countries *countries){
    std::string country_code;
    std::string file_name;
    if(std::cin >>country_code >> file_name){
        countries->INSERT(country_code, file_name);
    }
}   
// This is the entry point of our application
int main() {
    Countries *countries = new Countries();

    std::string command;

    // This is the loop of our application that handles the input
    while (1) {

        std::cin >> command;

        if (command == "EXIT") {
            delete countries; 
            return 0;
        }
        else if (command == "LOAD") {
            handle_load(countries);
        }
        else if (command == "LIST") {
            handle_list(countries);
        }
        else if (command == "RANGE") {
            handle_range(countries);
        }
        else if (command == "BUILD") {
            handle_build(countries);
        }
        else if (command == "FIND"){
            handle_find(countries);
        }
        else if (command == "DELETE") {
            handle_delete(countries);
        }
        else if (command == "LIMITS") {
            handle_limits(countries);
        }
        else if (command == "LOOKUP"){
            handle_lookup(countries);
        }
        else if (command == "REMOVE"){
            handle_remove(countries);
        }
        else if(command == "INSERT"){
            handle_insert(countries);
        }

    }
    delete countries;
    return 0;
}
