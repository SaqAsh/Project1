#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <unordered_map>
#include "Countries.h"
#include "g_node.h"

class Graph {
    private:
        Countries* countries;

        double getSeriesMean(Country* country, std::string series_code, bool& found);
        bool apart_of_threshold(double mean, double threshold, int op);
        bool addEdge(std::string code1, std::string code2, Edge edge);

    public:
        std::unordered_map<std::string, g_node> nodes;

        Graph();
        ~Graph();

        void LOAD(std::string filename);
        void INITIALIZE();
        void UPDATE_EDGES(std::string series_code, double threshold, std::string relation);
        void ADJACENT(std::string country_code);
        void PATH(std::string country_code1, std::string country_code2);
        void RELATIONSHIPS(std::string code1, std::string code2);
        bool isConnected(std::string country_code1, std::string country_code2);
};

#endif 
