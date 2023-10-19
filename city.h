#include <string>
#include <vector>

class City {
public:
    std::string name;
    int population;
    std::vector<City*> connections;

    City(const std::string& n, int p) : name(n), population(p) {}
};