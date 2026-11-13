
#ifndef SERVICES_H
#define SERVICES_H

#include "Graph.h"
#include <string>
#include <vector>

using namespace std;

struct Service {
    string serviceName;
    string serviceType;
    string location;
};

class Services {
private:
    const Graph& city;
    vector<Service> serviceList;

public:
    Services(const Graph& graph);

    void addService(
        const string& name,
        const string& type,
        const string& location
    );

    void displayServices() const;

    void findNearestService(
        const string& start,
        const string& serviceType
    ) const;

    bool loadFromFile(const string& filename);

    void saveToFile(const string& filename) const;
};

#endif
