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

void Graph::LOAD(const std::string& filename) {
    countries->LOAD(filename);
}

void Graph::INITIALIZE() {
    nodes.clear();

    for (int i = 0; i < 512; ++i) {
        Country* country = countries->country_array[i];
        if (country) {
            g_node node;
            node.country = country;
            nodes[country->country_code] = node;
        }
    }
}

void Graph::UPDATE_EDGES(const std::string& series_code, const std::string& thresholdStr, const std::string& relation) {
    double threshold = std::stod(thresholdStr);
    std::vector<std::string> country_vec;

    for (auto& pair : nodes) {
        bool found = false;
        double mean = 0.0;
        Node* curr = pair.second.country -> linked_list ->head;
        while (curr) {
            if (curr->data->series_code == series_code) {
                mean = curr->data->mean(); 
                found = true;
                break;
            }
            curr = curr->next;
        }
        if (!found) continue;
        bool qualifies = false;
        if (relation == "greater") {
            qualifies = mean > threshold;
        } else if (relation == "less") {
            qualifies = mean < threshold;
        } else if (relation == "equal") {
            qualifies = std::fabs(mean - threshold) < 1e-3;
        }

        if (qualifies) {
            country_vec.push_back(pair.second.country->country_code);
        }
    }

    bool flag = false;
    for (int  i = 0; i < country_vec.size(); i++) {
        for (int  j = i + 1; j < country_vec.size(); j++) {
            std::string country_code_1 = country_vec[i];
            std::string country_code_2 = country_vec[j];
            Edge edge(series_code, threshold, relation);
            auto& edges1 = nodes[country_code_1].neighbors[country_code_2];
            int  sizeBefore1 = edges1.size();
            edges1.insert(edge);
            auto& edges2 = nodes[country_code_2].neighbors[country_code_1];
            int  sizeBefore2 = edges2.size();
            edges2.insert(edge);
            if (edges1.size() > sizeBefore1 || edges2.size() > sizeBefore2) {
                flag = true;
            }
        }
    }
    flag ? std::cout << "success" << std::endl: std::cout << "failure" << std::endl;
}

void Graph::ADJACENT(const std::string& country_code) {
    if (nodes.find(country_code) == nodes.end()) {
        std::cout << "failure" << std::endl;
        return;
    }

    const std::unordered_map<std::string, std::set<Edge>>& neighbors = nodes[country_code].neighbors;
    if (neighbors.empty()) {
        std::cout << "none" << std::endl;
        return;
    }

    std::string result;
    for (const auto& pair : neighbors) {
        const std::string& neighbor_code = pair.first;
        if (nodes.find(neighbor_code) != nodes.end() && !nodes[neighbor_code].country->country_name.empty()) {
            result += nodes[neighbor_code].country->country_name + " ";
        }
    }

    if (result.empty()) {
        std::cout << "none" << std::endl;
    } else {
        result.pop_back(); // Remove trailing space.
        std::cout << result << std::endl;
    }
}

// PATH: Determine connectivity using BFS and print "true" or "false".
void Graph::PATH(const std::string& country_code1, const std::string& country_code2) {
    bool connected = isConnected(country_code1, country_code2);
    if (connected)
        std::cout << "true" << std::endl;
    else
        std::cout << "false" << std::endl;
}

bool Graph::isConnected(const std::string& country_code1, const std::string& country_code2) {
    if (country_code1 == country_code2) return true;
    if (nodes.find(country_code1) == nodes.end() || nodes.find(country_code2) == nodes.end()) return false;

    std::queue<std::string> q;
    std::unordered_set<std::string> visited;

    q.push(country_code1);
    visited.insert(country_code1);

    while (!q.empty()) {
        std::string curr = q.front();
        q.pop();
        if (curr == country_code2) return true;

        for (const auto& neighbor : nodes[curr].neighbors) {
            if (visited.find(neighbor.first) == visited.end()) {
                visited.insert(neighbor.first);
                q.push(neighbor.first);
            }
        }
    }
    return false;
}

void Graph::RELATIONSHIPS(const std::string& country_code_1, const std::string& country_code_2) {
    bool flag = false;
    if (nodes.find(country_code_1) == nodes.end() || nodes.find(country_code_2) == nodes.end()) {
        std::cout << "failure" << std::endl;
        return;
    }
    if (nodes[country_code_1].neighbors.find(country_code_2) == nodes[country_code_1].neighbors.end()) {
        std::cout << "none" << std::endl;
        return;
    }

    std::vector<Edge> edge_vec(nodes[country_code_1].neighbors[country_code_2].begin(), nodes[country_code_1].neighbors[country_code_2].end());

    for (int i = 0; i < edge_vec.size(); i++) {
        std::string threshold = std::to_string(edge_vec[i].threshold);
        if(!flag){
            std::cout << "(" << edge_vec[i].series_code << " "<< threshold << " "<< edge_vec[i].relation << ") ";
            flag = true;
        }
        else{
            std::cout << "(" << edge_vec[i].series_code << " "<< threshold << " "<< edge_vec[i].relation << ") ";
        }
    }

    if (!flag){
        std::cout << "none" << std::endl;  
        return ;
    } 
    std::cout<<std::endl;
}

