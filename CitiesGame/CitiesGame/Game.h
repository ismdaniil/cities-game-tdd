#pragma once
#include <string>
#include <vector>
#include <algorithm> // для std::find

class Game {
private:
    std::vector<std::string> citiesDatabase = { "Москва" };

public:
    bool IsCityExist(const std::string& city) const {
        // Используем алгоритм find вместо ручного цикла
        return std::find(citiesDatabase.begin(), citiesDatabase.end(), city) != citiesDatabase.end();
    }
};