#pragma once
#include <string>
#include <vector>
#include <algorithm> // дл€ std::find

class Game {
private:
    std::vector<std::string> citiesDatabase;

public:
    //  онструктор по умолчанию - ничего не инициализируем
    Game() = default;

    // ћетод дл€ загрузки базы данных
    void LoadDatabase(const std::vector<std::string>& database) {
        citiesDatabase = database;
    }

    bool IsCityExist(const std::string& city) const {
        return std::find(citiesDatabase.begin(), citiesDatabase.end(), city) != citiesDatabase.end();
    }
};