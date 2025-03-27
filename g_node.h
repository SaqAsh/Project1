#ifndef G_NODE_H
#define G_NODE_H

#include <unordered_map>
#include <set>
#include <string>
#include "Country.h"
#include "Edge.h"

class g_node {
public:
    Country* country;
    std::unordered_map<std::string, std::set<Edge>> neighbors;

    g_node() : country(nullptr) {}
};

#endif
