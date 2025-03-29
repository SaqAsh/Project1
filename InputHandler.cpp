#include <iostream>
#include <string>
#include "TimeSeries.h"
#include "Graph.h"

// This is the function that handles loading data from a file
void handle_load(Graph *graph){
    std::string filename;
    if(std::cin >> filename){
        graph->LOAD(filename);
    }
}

// This is the function that handles initializing a country's details
void handle_initialize(Graph *graph){
    graph->INITIALIZE();
    std::cout << "success" << std::endl;
}

// This is the function that handles computing the update_edges of a time series
void handle_update_edges(Graph *graph){
    std::string series_code;
    std::string threshold;
    std::string relation;
    if(std::cin >> series_code >> threshold >> relation){
        graph->UPDATE_EDGES(series_code, std::stod(threshold), relation); 
    }  
}

// This is the function that handles listing all countries adjacent to a given country
void handle_adjacent(Graph *graph){
    std::string country_code;
    if(std::cin >> country_code){
        graph->ADJACENT(country_code);
    }
}

// This is the function that handles checking if two countries are connected in the graph
void handle_path(Graph *graph){
    std::string country_code1;
    std::string country_code2;
    if(std::cin >> country_code1 >> country_code2){
        graph->PATH(country_code1, country_code2);
    }
}

// This is the function that handles listing all relationship_tuples between two countries
void handle_relationships(Graph *graph){
    std::string country_code1;
    std::string country_code2;
    if(std::cin >> country_code1 >> country_code2){
        graph->RELATIONSHIPS(country_code1, country_code2);
    }
}

int main() {
    Graph *graph = new Graph();
    std::string command;

    // This is the loop of our application that handles the input
    while (1) {

        std::cin >> command;

        if (command == "EXIT") {
            delete graph; 
            return 0;
        }
        else if (command == "LOAD") {
            handle_load(graph);
        }
        else if (command == "INITIALIZE") {
            handle_initialize(graph);
        }
        else if (command == "UPDATE_EDGES") {
            handle_update_edges(graph);
        }
        else if (command == "ADJACENT") {
            handle_adjacent(graph);
        }
        else if (command == "PATH") {
            handle_path(graph);
        }
        else if (command == "RELATIONSHIPS") {
            handle_relationships(graph);
        }
    }

    delete graph;
    return 0;
}
