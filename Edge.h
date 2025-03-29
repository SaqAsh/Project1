#ifndef EDGE_H
#define EDGE_H

#include <string>
#include <cmath>

class Edge {
public:
    std::string series_code;
    double threshold;
    std::string relation;

    Edge(std::string sc, double th, std::string rel) {
        series_code = sc;
        threshold = th;
        relation = rel;
    }

    // this is the operator overload

    bool operator<(Edge other) const {
        if (series_code != other.series_code) return series_code < other.series_code;
        if (std::fabs(threshold - other.threshold) > 1e-3) return threshold < other.threshold;
        return relation < other.relation;
    }
};

#endif
