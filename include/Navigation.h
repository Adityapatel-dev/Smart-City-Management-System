
#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "Graph.h"
#include <string>

using namespace std;

class Navigation {
private:
    const Graph& city;

public:
    Navigation(const Graph& graph);

    void findReachableLocations(const string& start);

    void findShortestRoute(
        const string& start,
        const string& destination
    );
};

#endif
