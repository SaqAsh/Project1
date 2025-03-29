#include "Graph.h"
#include <queue>
#include <set>
#include <cmath>
#include <iostream>
#include <unordered_set>

Graph::Graph() {
    countries = new Countries();
}

Graph::~Graph() {
    delete countries;
}

void Graph::LOAD(std::string filename) {
    countries->LOAD(filename);
}

/*

    CITATION:
    A  part of this function was generated with the help of chat.openai.com with the prompt:
    I wanna clear the unordered_map, how would I do that? I don't need a long explanation, just the code please.
    Where it gave me the .clear method
*/

//This is the function that initializes the graph by loading the countries into the graph
void Graph::INITIALIZE() {

    nodes.clear();

//loops through the countries and adds them to the graph`
    for (int i = 0; i < 512; ++i) {
        Country* country = countries->country_array[i];
        if (country) {
            g_node node;
            node.country = country;
            nodes[country->country_code] = node;
        }
    }
}

/*

    CITATION:
    A  part of this function was generated with the help of chat.openai.com with the prompt:
    I wanna clear the unordered_map, how would I do that? I don't need a long explanation, just the code please.
    Where it gave me the .clear method
    
    A  part of this function was generated with the help of chat.openai.com with the prompt:
    How do I extract the keys from an unordered_map<std::string, std::set<Edge>> using a for loop, can you give me the one liner for that? I don't need a long explanation, just the code please.
    I think it should be similar to python zip
*/
void Graph::UPDATE_EDGES(std::string series_code, double threshold, std::string relation) {
    int op = (relation == "less") ? 0 : (relation == "equal") ? 1 : (relation == "greater") ? 2 : -1;
    std::vector<std::string> qualifying_countries;

    for (std::pair<std::string, g_node> pair : nodes) {
        Country* country = pair.second.country;
        bool found = false;
        double mean = getSeriesMean(country, series_code, found);
        if (apart_of_threshold(mean, threshold, op) && found) qualifying_countries.push_back(country->country_code);
    }

    bool flag = false;

    //goes through permutations of the qualifying countries and adds edges between them

    for (int i = 0; i < qualifying_countries.size(); ++i) {
        for (int j = i + 1; j < qualifying_countries.size(); ++j) {
            Edge edge(series_code, threshold, relation);
            if (addEdge(qualifying_countries[i], qualifying_countries[j], edge)) flag = true;
        }
    }
    std::cout << (flag ? "success" : "failure") << std::endl;
}

/*
    CITATION:
    A  part of this function was generated with the help of chat.openai.com with the prompt:
    How do I extract the keys from an unordered_map<std::string, std::set<Edge>> using a for loop, can you give me the one liner for that? I don't need a long explanation, just the code please.
    I think it should be similar to python zip
*/
// This is the function that lists all countries adjacent to a given country
void Graph::ADJACENT(std::string country_code) {
    if (nodes.find(country_code) == nodes.end()) {
        std::cout << "failure" << std::endl;
        return;
    }

    std::unordered_map<std::string, std::set<Edge> > neighbors = nodes[country_code].neighbors;
    if (neighbors.empty()) {
        std::cout << "none" << std::endl;
        return;
    }

    //copies the keys of the neighbors into a vector to be able to iterate through it
    std::vector<std::string> keys;
    // using the pair to get the keys of the unordered_map
    for (std::pair<std::string, std::set<Edge> > pair : neighbors) {
        keys.push_back(pair.first);
    }

    bool flag = false;

    //iterating through the keys

    for (int i = 0; i < keys.size(); ++i) {
        if (nodes.find(keys[i]) != nodes.end() && !nodes[keys[i]].country->country_name.empty()) {
            std::cout << nodes[keys[i]].country->country_name << " ";
            flag = true;
        }
    }

    if (!flag) std::cout << "none";
    std::cout << std::endl;
}

// This is the function that checks if two countries are connected in the graph
void Graph::PATH(std::string country_code1, std::string country_code2) {
    std::cout << (isConnected(country_code1, country_code2) ? "true" : "false") << std::endl;
}

/*
    CITATION: 
    A  part of this function was generated with the help of chat.openai.com with the prompt, I wanna check to see if the country codes 
    inside the map are inside the map or not, how would I do that, I usually gotta do some weird iterator stuff with the maps. Give me the one liner to do 
    that please. 
    A  part of this function was generated with the help of chat.openai.com with the prompt:
    How do I extract the keys from an unordered_map<std::string, std::set<Edge>> using a for loop, can you give me the one liner for that? I don't need a long explanation, just the code please.
    I think it should be similar to python zip
*/
bool Graph::isConnected(std::string country_code1, std::string country_code2) {
    if (country_code1 == country_code2) return true;
    if (nodes.find(country_code1) == nodes.end() || nodes.find(country_code2) == nodes.end()) return false;

    std::queue<std::string> queue;
    std::unordered_set<std::string> visited;

    queue.push(country_code1);
    visited.insert(country_code1);

    while (!queue.empty()) {
        std::string current = queue.front();
        queue.pop();
        if (current == country_code2) return true;

        std::vector<std::string> neighbor_keys;
        for (std::pair<std::string, std::set<Edge> > element : nodes[current].neighbors) {
            neighbor_keys.push_back(element.first);
        }

        for (int i = 0; i < neighbor_keys.size(); ++i) {
            if (visited.find(neighbor_keys[i]) == visited.end()) {
                visited.insert(neighbor_keys[i]);
                queue.push(neighbor_keys[i]);
            }
        }
    }
    return false;
}

/*
    CITATION: 
    A  part of this function was generated with the help of chat.openai.com with the prompt, I wanna basically copy a set into 
    a vector and then be able to iterate through it, can you just give me the one line for that, I don't need ur long talk about the 
    history of a vector
*/

//This is the function that lists all the relationship between two countries
void Graph::RELATIONSHIPS(std::string country_code1, std::string country_code2) {
    if (nodes.find(country_code1) == nodes.end() || nodes.find(country_code2) == nodes.end()) {
        std::cout << "failure" << std::endl;
        return;
    }

    if (nodes[country_code1].neighbors.find(country_code2) == nodes[country_code1].neighbors.end()) {
        std::cout << "none" << std::endl;
        return;
    }

    // copies the set into a vector to be able to iterate through it
    std::vector<Edge> edge_vec(nodes[country_code1].neighbors[country_code2].begin(),nodes[country_code1].neighbors[country_code2].end());

    //run through the vector and print out the edges
    for (int i = 0; i < edge_vec.size(); ++i) {
        std::cout << "(" << edge_vec[i].series_code << " " << edge_vec[i].threshold << " " << edge_vec[i].relation << ") ";
    }

    if (!edge_vec.size()) std::cout << "none";
    std::cout << std::endl;
}

// Loops through the linked list of the country to find the time series of interest and returns the mean of that time series
double Graph::getSeriesMean(Country* country, std::string series_code, bool& found) {
    Node* curr = country->linked_list->head;

    // loops through the linked list to find the time series of interest

    while (curr) {
        if (curr->data->series_code == series_code) {
            found = true; // pass by reference value that changes the value passed in
            return curr->data->mean();
        }
        curr = curr->next;
    }
    found = false;
    return 0.0;
}

// Checks to see if the mean is less than, equal to, or greater than the threshold
bool Graph::apart_of_threshold(double mean, double threshold, int op) {
    return (op == 0) ? (mean < threshold):(op == 1) ? (std::fabs(mean - threshold) < 1e-3):(op == 2) ? (mean > threshold): false;
}

/*

    CITATION:
    A  part of this function was generated with the help of chat.openai.com with the prompt:
    I wanna check to see if something has been added to a set, how would I do that? I don't need a long explanation, just the code please.
    Where it gave me the .size() method and then the idea of checking the size before and after the insertion
*/

// Adds an edge between two countries in the graph
// and returns true if the edge was added successfully, false otherwise
// And the way this is returned is via checking the size of the set before and after the insertion
bool Graph::addEdge(std::string country_code1, std::string country_code2, Edge edge) {
    std::set<Edge>& edges_1 = nodes[country_code1].neighbors[country_code2];
    std::set<Edge>& edges_2 = nodes[country_code2].neighbors[country_code1];
    int prev_1 = edges_1.size();
    int prev_2 = edges_2.size();
    edges_1.insert(edge);
    edges_2.insert(edge);
    return edges_1.size() > prev_1 || edges_2.size() > prev_2;
}

