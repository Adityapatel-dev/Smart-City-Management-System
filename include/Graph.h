
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Graph {
private:
    unordered_map<string, vector<pair<string, int>>> adjList;

public:
    void addLocation(const string& location);

    void addRoad(
        const string& source,
        const string& destination,
        int distance
    );

    void displayNetwork() const;

    bool locationExists(const string& location) const;

    const unordered_map<string, vector<pair<string, int>>>&
    getAdjList() const;

    bool loadFromFiles(
        const string& locationsFile,
        const string& roadsFile
    );

    void saveToFiles(
        const string& locationsFile,
        const string& roadsFile
    ) const;
};

#endif
