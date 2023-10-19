#include "city.h"
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <queue>

using namespace std;

// task2
map<string, City*> read_city_population(const string& filename) {
    map<string, City*> cities;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        string city_name, population_s;
        if (line.find(':') != string::npos) {
            city_name = line.substr(0, line.find(':')-1);
            population_s = line.substr(line.find(':') + 2);
        }

        int population = stoi(population_s);
        // cout << city_name << population << endl;
        City* city = new City(city_name, population);
        cities[city_name] = city;
    }

    return cities;
}

void read_road_network(const string& filename, map<string, City*>& cities) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        string city1_name, city2_name;
        if (line.find(':') != string::npos) {
            city1_name = line.substr(0, line.find(':') - 1);
            city2_name = line.substr(line.find(':') + 2);
        }
        // cout << city1_name << " " << city2_name << endl;
        if (cities.find(city1_name) == cities.end()){
            cout << city1_name << " data not found\n";
            continue;
        }

        if (cities.find(city2_name) == cities.end()){
            cout << city2_name << " data not found\n";
            continue;
        }
        
        City* city1 = cities[city1_name];
        City* city2 = cities[city2_name];
        if (city1 && city2) {
            city1->connections.push_back(city2);
            city2->connections.push_back(city1);
        }
    }
}

void print_cities(map<string, City*> cities) {
    for (auto& city : cities){
        cout << city.first << " " << city.second->population << endl;
        for (auto& city2 : city.second->connections){
            cout << city2->name << "---";
        }
        cout << endl;
    }
}

// task3: find the number of islands
// bfs from point city, mark all cities it could visit as visited
void bfs(City* city, set<string>& visited) {
    // cout << "---1---";
    queue<City*> queue;
    queue.push(city);

    while (!queue.empty()) {
        City* currentCity = queue.front();
        queue.pop();

        for (City* neighbor : currentCity->connections) {
            if (visited.find(neighbor->name) == visited.end()) {
                visited.insert(neighbor->name);
                queue.push(neighbor);
            }
        }
    }
}

int count_islands(map<string, City*>& cities) {
    set<string> visited;
    int islands = 0;

    for (auto& item : cities) {
        string city_name = item.first;
        if (visited.find(city_name) == visited.end()) {
            City* city = cities[city_name];
            visited.insert(city_name);
            bfs(city, visited);
            islands++;
        }
    }

    return islands;
}


// task4: find the population of each island (connected component) in the graph
// bfs to calculate population on an island
void bfs2(City* city, std::set<string>& visited, int& population) {
    std::queue<City*> queue;
    queue.push(city);

    while (!queue.empty()) {
        City* curr_city = queue.front();
        queue.pop();
        population += curr_city->population;

        for (City* neighbor : curr_city->connections) {
            if (visited.find(neighbor->name) == visited.end()) {
                visited.insert(neighbor->name);
                queue.push(neighbor);
            }
        }
    }
}

map<string, int> get_island_populations(map<string, City*>& cities) {
    set<string> visited;
    map<string, int> res;

    for (auto& item : cities) {
        string city_name = item.first;
        if (visited.find(city_name) == visited.end()) {
            int population = 0;
            City* city = cities[city_name];
            visited.insert(city_name);
            bfs2(city, visited, population);
            res[city_name] = population;
        }
    }

    return res;
}

// task5: find the minimum number of unique highways from one city to another
int find_minimum_highways(City* city1, City* city2) {
    std::queue<std::pair<City*, int>> queue;
    std::set<City*> visited;
    
    queue.push({city1, 0});
    visited.insert(city1);

    while (!queue.empty()) {
        City* curr_city = queue.front().first;
        int distance = queue.front().second;
        queue.pop();

        if (curr_city == city2) {
            return distance;
        }

        for (City* neighbor : curr_city->connections) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                queue.push({neighbor, distance + 1});
            }
        }
    }
    // no avaliable route
    return -1; 
}


void test4(){
    map<string, City*> cities; // map from city name to city object;
    cities = read_city_population("city_population.txt");
    read_road_network("road_network.txt", cities);

    // print_cities(cities);
    // vector<string> cities_lst = {"Yuma", "Beaverton", "Apple Valley","Quincy","Manchester"};
    int n_island = count_islands(cities);
    cout << "number of islands is " << n_island << endl;
    map<string,int> populations = get_island_populations(cities);
    for (auto & iter : populations){
        cout << "population of the island with "<< iter.first << " on it is "<< iter.second << endl;
    }

    // cities_lst = {"Huntington Park","Wilmington","Berwyn"};
    // n_island = count_islands(cities, cities_lst);
    // cout << "number of islands is " << n_island << endl;
    // populations = get_island_populations(cities, cities_lst);
    // for (auto & iter : populations){
    //     cout << "population of the island with "<< iter.first << " on it is "<< iter.second << endl;
    // }

    // cities_lst = {"Huntington Park","Wilmington","Berwyn", "Wichita Falls"};
    // n_island = count_islands(cities, cities_lst);
    // cout << "number of islands is " << n_island << endl;
    // populations = get_island_populations(cities, cities_lst);
    // for (auto & iter : populations){
    //     cout << "population of the island with "<< iter.first << " on it is "<< iter.second << endl;
    // }

    string c1 = "Huntington Park";
    string c2 = "Wilmington";
    cout << "minimum highways between " << c1 << " and " << c2 << " is " \
     << find_minimum_highways(cities[c1], cities[c2]) << endl;

    c1 = "Wichita Falls";
    c2 = "Wilmington";
    cout << "minimum highways between " << c1 << " and " << c2 << " is " \
     << find_minimum_highways(cities[c1], cities[c2]) << endl;

    c1 = "Huntington Park";
    c2 = "Berwyn";
    cout << "minimum highways between " << c1 << " and " << c2 << " is " \
     << find_minimum_highways(cities[c1], cities[c2]) << endl;

    c1 = "Quincy";
    c2 = "Binghamton";
    cout << "minimum highways between " << c1 << " and " << c2 << " is " \
     << find_minimum_highways(cities[c1], cities[c2]) << endl;

    c1 = "New Berlin";
    c2 = "Binghamton";
    cout << "minimum highways between " << c1 << " and " << c2 << " is " \
     << find_minimum_highways(cities[c1], cities[c2]) << endl;
}
