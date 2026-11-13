# Smart City Management System

A menu-driven C++17 Data Structures and Algorithms project that models a city road network, finds routes, and manages emergency services.

## Overview

The Smart City Management System represents city locations as vertices and roads as weighted, undirected edges. Users can manage locations and roads, explore reachable locations, calculate shortest routes, and locate nearby emergency services based on road distance. City data is stored in text files and loaded again when the application starts.

## Features

- Add city locations and weighted road connections.
- Display the city road network.
- Find reachable locations using Breadth-First Search (BFS).
- Find shortest-distance routes using Dijkstra's algorithm.
- Add and display hospitals, police stations, and fire stations.
- Find the nearest service of a selected type from a starting location.
- Load and save locations, roads, and services using text files.
- Use an interactive console menu to operate the application.

## Technologies

- C++17
- GCC / G++ compiler
- Standard C++ Library
- Text-file persistence

## Data Structures and Algorithms

| Concept | Use in this project |
|---|---|
| Graph | Models locations and road connections |
| Adjacency list | Stores each location's neighbouring locations and road distances |
| Queue | Supports BFS traversal |
| Priority queue | Supports Dijkstra's shortest-path search |
| `unordered_map` | Stores graph adjacency and distance information |
| `vector` | Stores neighbouring roads and emergency services |

### Algorithms

**Breadth-First Search (BFS):** Traverses the road network from a starting location and lists reachable locations.

**Dijkstra's algorithm:** Calculates minimum road distance from a starting location. The same shortest-distance approach is used to identify the nearest matching emergency service. Road weights must be positive.

## Project Structure

```text
Smart_City_Management/
├── src/
│   ├── main.cpp
│   ├── Graph.cpp
│   ├── Navigation.cpp
│   └── Services.cpp
├── include/
│   ├── Graph.h
│   ├── Navigation.h
│   └── Services.h
├── data/
│   ├── locations.txt
│   ├── roads.txt
│   └── services.txt
├── screenshots/
│   └── Smart_City_Management_System_Output.png
├── docs/
├── .gitignore
└── README.md
```

## Build and Run

### Prerequisites

- A C++17-compatible GCC/G++ compiler.
- Windows PowerShell or another terminal.

### Compile

Run this command from the project root directory:

```powershell
g++ -std=c++17 -Wall -Wextra -I include src/main.cpp src/Graph.cpp src/Navigation.cpp src/Services.cpp -o SmartCity.exe
```

### Run on Windows

```powershell
.\SmartCity.exe
```

**Important:** Run the executable from the project root so the relative paths to the `data` directory resolve correctly.

## Application Menu

```text
1. Add City Location
2. Add Road
3. Display City Road Network
4. Find Reachable Locations (BFS)
5. Find Shortest Route (Dijkstra)
6. Add Emergency Service
7. Display Emergency Services
8. Find Nearest Hospital
9. Find Nearest Police Station
10. Find Nearest Fire Station
11. Save Data
0. Save and Exit
```

## Sample Results

Using the sample city data, the shortest route from Central Station to Airport is:

```text
Central Station -> Police Station -> City Mall -> Airport
Total Distance: 15 km
```

Nearest emergency services from Central Station in the sample data:

| Service | Location | Road distance |
|---|---|---:|
| Hospital | City Hospital | 5 km |
| Police Station | Police Station | 3 km |
| Fire Station | City Mall | 7 km |

These values correspond to the sample roads and services stored in the `data` directory.

## Data Files

- `data/locations.txt`: one city location per line.
- `data/roads.txt`: road records in `source|destination|distance` format.
- `data/services.txt`: service records in `name|type|location` format.

The application loads these files at startup and saves changes when the user selects **Save Data** or **Save and Exit**.

## Testing Performed

The project has been manually tested for:

- Adding locations and roads through the menu.
- Displaying the road network.
- BFS reachability traversal.
- Dijkstra shortest-route calculation.
- Adding and listing emergency services.
- Finding nearest hospital, police station, and fire station.
- Saving data and loading it again after restarting the application.

## Limitations

- The application uses a console interface and sample city data rather than a live map.
- Distances are static values entered into the road data file; live traffic and road closures are not modelled.
- Text-file persistence is intended for this educational project and does not provide database transactions or multi-user access.

## Future Enhancements

- Add a graphical user interface and map visualization.
- Integrate live traffic and road-closure information.
- Add emergency contact details and service availability.
- Add stronger validation and automated unit tests.
- Move persistent data to a database.

## Project Information

- **Project:** Smart City Management System
- **Course:** MCA Data Structures and Algorithms Mini Project
- **Language:** C++17
- **Author:** Aditya Patel

---

This project was developed for educational purposes to demonstrate practical applications of graphs, BFS, Dijkstra's algorithm, and file handling in C++.
