#include <iostream>
#include <string>
#include "TimeSeries.h"
#include "Country.h"
//This is the function that handles the load command, it takes the TimeSeries object and loads the file using the LOAD function 
void handle_load(Country *&country) {
    std::string country_name;
    std::cin.ignore();
    std::getline(std::cin, country_name);
    delete country;
    country = new Country();  
    country->LOAD(country_name);
    std::cout << "success" << std::endl;
    
}


//takes in the time series object and adds a new data point using the add function
void handle_add(Country *country){
    std::string series_code;
    double year;
    double data;
    if (std::cin >> series_code >> year >> data) {
        country->ADD(year, data, series_code);
    }
}
void handle_print(Country *country){
    std::string series_code;
    if (std::cin >> series_code) {
        country->PRINT(series_code);
    }
}
//takes in the time series object and updates a new data point using the update function
void handle_update(Country *country){
    std::string series_code;
    double year;
    double data;
    if (std::cin >> series_code >> year >> data) {
        country->UPDATE(year, data, series_code);
    }
}
void handle_delete(Country *country){
    std::string series_code;
    if (std::cin >> series_code) {
        country->DELETE(series_code);
    }
}

//this is the entry point of our application 
int main() {
    Country *country = new Country();

    std::string command;

    //this is the loop of our application that handles the input
    while (1) {

        std::cin >> command;

        if (command == "EXIT") {
            delete country; 
            return 0;
        }
        else if (command == "LOAD") {
            handle_load(country);
        }
        else if (command == "PRINT") {
            handle_print(country);
        }
        else if (command == "ADD") {
            handle_add(country);
        }
        else if (command == "UPDATE") {
            handle_update(country);
        }
        else if (command == "LIST"){
            country->LIST();
        }
        else if (command == "DELETE") {
            handle_delete(country);
        }
        else if (command == "BIGGEST"){
            country->BIGGEST();
        }
    }
    delete country;
    return 0;
}
