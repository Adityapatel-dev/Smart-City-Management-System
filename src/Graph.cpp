
#include "../include/Graph.h"

#include <fstream>
#include <sstream>

void Graph::addLocation(const string& location) {
    if (location.empty() || locationExists(location)) {
        cout << "Location already exists or is invalid!\n";
        return;
    }

    adjList[location];
    cout << "Location added successfully!\n";
}

bool Graph::locationExists(const string& location) const {
    return adjList.find(location) != adjList.end();
}

void Graph::addRoad(
    const string& source,
    const string& destination,
    int distance
) {
    if (!locationExists(source) || !locationExists(destination)) {
        cout << "One or both locations do not exist!\n";
        return;
    }

    if (source == destination || distance <= 0) {
        cout << "Invalid road details!\n";
        return;
    }

    adjList[source].push_back({destination, distance});
    adjList[destination].push_back({source, distance});

    cout << "Road added successfully!\n";
}

void Graph::displayNetwork() const {
    if (adjList.empty()) {
        cout << "No locations available.\n";
        return;
    }

    cout << "\n===== CITY ROAD NETWORK =====\n";

    for (const auto& location : adjList) {
        cout << location.first << " -> ";

        if (location.second.empty()) {
            cout << "No connected roads";
        } else {
            for (const auto& road : location.second) {
                cout << "[" << road.first
                     << ", " << road.second << " km] ";
            }
        }

        cout << "\n";
    }
}

const unordered_map<string, vector<pair<string, int>>>&
Graph::getAdjList() const {
    return adjList;
}

// Load locations and roads from text files
bool Graph::loadFromFiles(
    const string& locationsFile,
    const string& roadsFile
) {
    ifstream locationInput(locationsFile);

    if (!locationInput.is_open()) {
        cerr << "Unable to open locations file!\n";
        return false;
    }

    string location;
    int loadedLocations = 0;

    while (getline(locationInput, location)) {
        if (!location.empty() && !locationExists(location)) {
            adjList[location];
            loadedLocations++;
        }
    }

    locationInput.close();

    ifstream roadInput(roadsFile);

    if (!roadInput.is_open()) {
        cerr << "Unable to open roads file!\n";
        return false;
    }

    string line;
    int loadedRoads = 0;

    while (getline(roadInput, line)) {
        stringstream ss(line);

        string source;
        string destination;
        string distanceText;

        if (!getline(ss, source, '|') ||
            !getline(ss, destination, '|') ||
            !getline(ss, distanceText)) {
            cerr << "Skipping invalid road record.\n";
            continue;
        }

        try {
            size_t position = 0;
            int distance = stoi(distanceText, &position);

            if (position != distanceText.size() ||
                distance <= 0 ||
                source == destination ||
                !locationExists(source) ||
                !locationExists(destination)) {
                cerr << "Skipping invalid road record.\n";
                continue;
            }

            addRoad(source, destination, distance);
            loadedRoads++;
        } catch (...) {
            cerr << "Skipping road with invalid distance.\n";
        }
    }

    roadInput.close();

    cout << "\nLocations loaded: " << loadedLocations << "\n";
    cout << "Roads loaded: " << loadedRoads << "\n";

    return loadedLocations > 0;
}

// Save locations and roads to text files
void Graph::saveToFiles(
    const string& locationsFile,
    const string& roadsFile
) const {
    ofstream locationOutput(locationsFile);
    ofstream roadOutput(roadsFile);

    if (!locationOutput.is_open() || !roadOutput.is_open()) {
        cerr << "Unable to save city data!\n";
        return;
    }

    for (const auto& location : adjList) {
        locationOutput << location.first << "\n";

        for (const auto& road : location.second) {
            // Save each undirected road only once
            if (location.first < road.first) {
                roadOutput << location.first << "|"
                           << road.first << "|"
                           << road.second << "\n";
            }
        }
    }

    locationOutput.close();
    roadOutput.close();

    cout << "City data saved successfully!\n";
}
