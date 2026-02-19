#pragma once
#include <string>
#include <vector>
#include <algorithm> // для std::find

class Game {
private:
    std::vector<std::string> citiesDatabase;

public:
    // Конструктор по умолчанию - ничего не инициализируем
    Game() = default;

    // Метод для загрузки базы данных
    void LoadDatabase(const std::vector<std::string>& database) {
        if (database.empty()) {
            // Можно выбросить исключение или просто очистить базу
            citiesDatabase.clear();
            return;
        }
        citiesDatabase = database;
    }

    bool IsCityExist(const std::string& city) const {
        return std::find(citiesDatabase.begin(), citiesDatabase.end(), city) != citiesDatabase.end();
    }

};