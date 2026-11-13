
#include "../include/Services.h"

#include <iostream>
#include <queue>
#include <unordered_map>
#include <limits>
#include <fstream>
#include <sstream>

using namespace std;

Services::Services(const Graph& graph) : city(graph) {
}

void Services::addService(
    const string& name,
    const string& type,
    const string& location
) {
    if (!city.locationExists(location) ||
        name.empty() ||
        (type != "Hospital" &&
         type != "Police Station" &&
         type != "Fire Station")) {
        cout << "Invalid service details!\n";
        return;
    }

    for (const auto& service : serviceList) {
        if (service.serviceName == name) {
            cout << "Service already exists!\n";
            return;
        }
    }

    serviceList.push_back({name, type, location});

    cout << "Emergency service added successfully!\n";
}

void Services::displayServices() const {
    cout << "\n===== EMERGENCY SERVICES =====\n";

    if (serviceList.empty()) {
        cout << "No emergency services available.\n";
        return;
    }

    for (const auto& service : serviceList) {
        cout << "Name: " << service.serviceName
             << " | Type: " << service.serviceType
             << " | Location: " << service.location
             << "\n";
    }
}

void Services::findNearestService(
    const string& start,
    const string& serviceType
) const {
    const auto& graph = city.getAdjList();

    if (!city.locationExists(start)) {
        cout << "Starting location not found!\n";
        return;
    }

    if (serviceType != "Hospital" &&
        serviceType != "Police Station" &&
        serviceType != "Fire Station") {
        cout << "Invalid service type!\n";
        return;
    }

    const int INF = numeric_limits<int>::max();

    unordered_map<string, int> distance;

    for (const auto& location : graph) {
        distance[location.first] = INF;
    }

    using Node = pair<int, string>;

    priority_queue<
        Node,
        vector<Node>,
        greater<Node>
    > pq;

    distance[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int currentDistance = pq.top().first;
        string current = pq.top().second;
        pq.pop();

        if (currentDistance > distance[current]) {
            continue;
        }

        for (const auto& road : graph.at(current)) {
            string neighbour = road.first;
            int weight = road.second;

            if (currentDistance <= INF - weight &&
                currentDistance + weight < distance[neighbour]) {

                distance[neighbour] = currentDistance + weight;
                pq.push({distance[neighbour], neighbour});
            }
        }
    }

    const Service* nearest = nullptr;
    int minimumDistance = INF;

    for (const auto& service : serviceList) {
        if (service.serviceType != serviceType) {
            continue;
        }

        int serviceDistance = distance[service.location];

        if (serviceDistance < minimumDistance) {
            minimumDistance = serviceDistance;
            nearest = &service;
        }
    }

    if (nearest == nullptr || minimumDistance == INF) {
        cout << "\nNo reachable " << serviceType
             << " found from " << start << ".\n";
        return;
    }

    cout << "\n===== NEAREST " << serviceType << " =====\n";
    cout << "Service Name: " << nearest->serviceName << "\n";
    cout << "Location: " << nearest->location << "\n";
    cout << "Starting Point: " << start << "\n";
    cout << "Distance: " << minimumDistance << " km\n";
}

// Load emergency services
bool Services::loadFromFile(const string& filename) {
    ifstream input(filename);

    if (!input.is_open()) {
        cerr << "Unable to open services file!\n";
        return false;
    }

    string line;
    int loadedServices = 0;

    while (getline(input, line)) {
        stringstream ss(line);

        string name;
        string type;
        string location;

        if (!getline(ss, name, '|') ||
            !getline(ss, type, '|') ||
            !getline(ss, location)) {
            cerr << "Skipping invalid service record.\n";
            continue;
        }

        if (!city.locationExists(location) ||
            name.empty() ||
            (type != "Hospital" &&
             type != "Police Station" &&
             type != "Fire Station")) {
            cerr << "Skipping invalid service record.\n";
            continue;
        }

        bool duplicate = false;

        for (const auto& service : serviceList) {
            if (service.serviceName == name) {
                duplicate = true;
                break;
            }
        }

        if (!duplicate) {
            serviceList.push_back({name, type, location});
            loadedServices++;
        }
    }

    input.close();

    cout << "Emergency services loaded: "
         << loadedServices << "\n";

    return loadedServices > 0;
}

// Save emergency services
void Services::saveToFile(const string& filename) const {
    ofstream output(filename);

    if (!output.is_open()) {
        cerr << "Unable to save services file!\n";
        return;
    }

    for (const auto& service : serviceList) {
        output << service.serviceName << "|"
               << service.serviceType << "|"
               << service.location << "\n";
    }

    output.close();

    cout << "Emergency services saved successfully!\n";
}
