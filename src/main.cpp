
#include "../include/Graph.h"
#include "../include/Navigation.h"
#include "../include/Services.h"

#include <iostream>
#include <limits>
#include <string>

using namespace std;

// Read an integer safely
int readInteger(const string& message) {
    int value;

    while (true) {
        cout << message;

        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cout << "Invalid input! Please enter a number.\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Read a complete line of text
string readText(const string& message) {
    string value;

    cout << message;
    getline(cin, value);

    return value;
}

// Display main menu
void displayMenu() {
    cout << "\n============================================\n";
    cout << "       SMART CITY MANAGEMENT SYSTEM\n";
    cout << "============================================\n";

    cout << "1. Add City Location\n";
    cout << "2. Add Road\n";
    cout << "3. Display City Road Network\n";
    cout << "4. Find Reachable Locations (BFS)\n";
    cout << "5. Find Shortest Route (Dijkstra)\n";
    cout << "6. Add Emergency Service\n";
    cout << "7. Display Emergency Services\n";
    cout << "8. Find Nearest Hospital\n";
    cout << "9. Find Nearest Police Station\n";
    cout << "10. Find Nearest Fire Station\n";
    cout << "11. Save Data\n";
    cout << "0. Save and Exit\n";

    cout << "============================================\n";
}

// Save all project data
void saveData(const Graph& city, const Services& services) {
    city.saveToFiles(
        "data/locations.txt",
        "data/roads.txt"
    );

    services.saveToFile("data/services.txt");
}

int main() {

    Graph city;

    cout << "\nLoading Smart City data...\n";

    // Load city locations and roads
    if (!city.loadFromFiles(
            "data/locations.txt",
            "data/roads.txt")) {

        cout << "Unable to load city data.\n";
        cout << "Please check the files inside the data folder.\n";

        return 1;
    }

    // Create navigation and services objects
    Navigation navigation(city);
    Services services(city);

    // Load emergency services
    services.loadFromFile("data/services.txt");

    cout << "\nCity data loaded successfully!\n";

    int choice;

    do {
        displayMenu();

        choice = readInteger("Enter your choice: ");

        switch (choice) {

            case 1: {
                string location = readText("Enter location name: ");

                city.addLocation(location);
                break;
            }

            case 2: {
                string source = readText("Enter starting location: ");

                string destination =
                    readText("Enter destination location: ");

                int distance =
                    readInteger("Enter road distance in km: ");

                city.addRoad(source, destination, distance);
                break;
            }

            case 3: {
                city.displayNetwork();
                break;
            }

            case 4: {
                string start =
                    readText("Enter starting location: ");

                navigation.findReachableLocations(start);
                break;
            }

            case 5: {
                string start =
                    readText("Enter starting location: ");

                string destination =
                    readText("Enter destination location: ");

                navigation.findShortestRoute(start, destination);
                break;
            }

            case 6: {
                string name =
                    readText("Enter emergency service name: ");

                cout << "\nSelect service type:\n";
                cout << "1. Hospital\n";
                cout << "2. Police Station\n";
                cout << "3. Fire Station\n";

                int typeChoice =
                    readInteger("Enter service type: ");

                string type;

                switch (typeChoice) {
                    case 1:
                        type = "Hospital";
                        break;

                    case 2:
                        type = "Police Station";
                        break;

                    case 3:
                        type = "Fire Station";
                        break;

                    default:
                        cout << "Invalid service type!\n";
                        break;
                }

                if (!type.empty()) {
                    string location =
                        readText("Enter service location: ");

                    services.addService(name, type, location);
                }

                break;
            }

            case 7: {
                services.displayServices();
                break;
            }

            case 8: {
                string start =
                    readText("Enter your current location: ");

                services.findNearestService(start, "Hospital");
                break;
            }

            case 9: {
                string start =
                    readText("Enter your current location: ");

                services.findNearestService(start, "Police Station");
                break;
            }

            case 10: {
                string start =
                    readText("Enter your current location: ");

                services.findNearestService(start, "Fire Station");
                break;
            }

            case 11: {
                saveData(city, services);
                break;
            }

            case 0: {
                cout << "\nSaving project data before exit...\n";

                saveData(city, services);

                cout << "\nThank you for using Smart City Management System!\n";
                break;
            }

            default: {
                cout << "Invalid choice! Please select a valid option.\n";
                break;
            }
        }

    } while (choice != 0);

    return 0;
}
