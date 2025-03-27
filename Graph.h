#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <unordered_map>
#include "Countries.h"
#include "g_node.h"

class Graph {
private:
    Countries* countries;
public:
    // Map of nodes keyed by country code.
    std::unordered_map<std::string, g_node> nodes;

    Graph();
    ~Graph();

    // Loads the file and prints "success".
    void LOAD(const std::string& filename);

    // Initializes the graph (rebuilds nodes from country_array) and prints "success".
    void INITIALIZE();

    // Updates edges based on the given time series criteria.
    // Prints "success" if at least one new edge was added, otherwise prints "failure".
    void UPDATE_EDGES(const std::string& series_code, const std::string& thresholdStr, const std::string& relation);

    // Prints a space-separated list of neighbor country names.
    // Prints "failure" if the country doesn't exist or "none" if no neighbors exist.
    void ADJACENT(const std::string& country_code);

    // Uses BFS to check connectivity between two countries and prints "true" or "false".
    void PATH(const std::string& country_code1, const std::string& country_code2);

    // Prints the relationship tuples between two countries.
    // Prints "failure" if a country is missing or "none" if no edge exists.
    void RELATIONSHIPS(const std::string& code1, const std::string& code2);

    // Helper: returns true if there is a connection between two countries.
    bool isConnected(const std::string& country_code1, const std::string& country_code2);
};

#endif // GRAPH_H
