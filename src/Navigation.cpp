
#include "../include/Navigation.h"

#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <limits>
#include <algorithm>

Navigation::Navigation(const Graph& graph) : city(graph) {
}

// BFS: Find all reachable locations
void Navigation::findReachableLocations(const string& start) {
    const auto& graph = city.getAdjList();

    if (!city.locationExists(start)) {
        cout << "\nStarting location not found!\n";
        return;
    }

    queue<string> q;
    unordered_set<string> visited;

    q.push(start);
    visited.insert(start);

    cout << "\n===== REACHABLE LOCATIONS (BFS) =====\n";

    while (!q.empty()) {
        string current = q.front();
        q.pop();

        cout << current << "\n";

        for (const auto& road : graph.at(current)) {
            string neighbour = road.first;

            if (visited.find(neighbour) == visited.end()) {
                visited.insert(neighbour);
                q.push(neighbour);
            }
        }
    }
}

// Dijkstra: Find shortest route
void Navigation::findShortestRoute(
    const string& start,
    const string& destination
) {
    const auto& graph = city.getAdjList();

    if (!city.locationExists(start) ||
        !city.locationExists(destination)) {
        cout << "\nStarting or destination location not found!\n";
        return;
    }

    const int INF = numeric_limits<int>::max();

    unordered_map<string, int> distance;
    unordered_map<string, string> parent;

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
                parent[neighbour] = current;

                pq.push({distance[neighbour], neighbour});
            }
        }
    }

    if (distance[destination] == INF) {
        cout << "\nNo route available between these locations.\n";
        return;
    }

    vector<string> path;
    string current = destination;

    while (current != start) {
        path.push_back(current);

        if (parent.find(current) == parent.end()) {
            cout << "Unable to construct route.\n";
            return;
        }

        current = parent[current];
    }

    path.push_back(start);
    reverse(path.begin(), path.end());

    cout << "\n===== SHORTEST ROUTE (DIJKSTRA) =====\n";

    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];

        if (i < path.size() - 1) {
            cout << " -> ";
        }
    }

    cout << "\nTotal Distance: "
         << distance[destination] << " km\n";
}
