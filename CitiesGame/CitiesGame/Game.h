#pragma once
#include <string>
#include <vector>

class Game {
private:
    std::vector<std::string> citiesDatabase = { "Москва" }; // Минимальная база для одного теста

public:
    bool IsCityExist(const std::string& city) {
        for (const auto& c : citiesDatabase) {
            if (c == city) return true;
        }
        return false;
    }
};