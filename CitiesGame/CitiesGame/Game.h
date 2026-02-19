#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <locale>
#include <codecvt>
#include <iostream>

class Game {
private:
    std::vector<std::string> citiesDatabase;
    std::vector<std::string> usedCities;
    std::vector<std::string> players;
    int currentPlayerIndex = 0;
    static const std::string FORBIDDEN_LETTERS;

    // Вспомогательный метод для приведения русских букв к нижнему регистру
    char ToLowerRussian(char c) const {
        if (c >= 'А' && c <= 'Я') {
            return c + 32; // В ASCII/CP1251 русские буквы идут с интервалом 32
        }
        if (c >= 'A' && c <= 'Z') {
            return c + 32; // Английские в нижний регистр
        }
        return c;
    }

public:
    Game() = default;

    void LoadDatabase(const std::vector<std::string>& database) {
        if (database.empty()) {
            citiesDatabase.clear();
            return;
        }
        citiesDatabase = database;
    }

    bool IsCityExist(const std::string& city) const {
        return std::find(citiesDatabase.begin(), citiesDatabase.end(), city) != citiesDatabase.end();
    }

    // Получить последнюю значимую букву (пропуская Ъ, Ы, Ь)
    char GetLastSignificantChar(const std::string& city) const {
        if (city.empty()) return '\0';

        // Ищем последний значимый символ с конца
        for (int i = city.length() - 1; i >= 0; i--) {
            char currentChar = city[i];
            // Проверяем, не является ли текущий символ запрещенным
            if (FORBIDDEN_LETTERS.find(currentChar) == std::string::npos) {
                return ToLowerRussian(currentChar);
            }
        }

        // Если все символы запрещенные (маловероятно), возвращаем последний
        return ToLowerRussian(city.back());
    }

    // Проверить, подходит ли следующий город по правилу последней буквы
    bool IsValidNextCity(const std::string& lastCity, const std::string& nextCity) const {
        if (lastCity.empty() || nextCity.empty()) return true; // Для первого хода всегда true

        char lastChar = GetLastSignificantChar(lastCity);
        char firstChar = ToLowerRussian(nextCity[0]);

        return lastChar == firstChar;
    }

    // Добавить город в список использованных
    bool AddCity(const std::string& city) {
        if (!IsCityExist(city)) {
            return false;
        }

        if (IsCityUsed(city)) {
            return false;
        }

        usedCities.push_back(city);
        return true;
    }

    // Проверить, использовался ли город
    bool IsCityUsed(const std::string& city) const {
        return std::find(usedCities.begin(), usedCities.end(), city) != usedCities.end();
    }

    // Получить последний использованный город
    std::string GetLastCity() const {
        if (usedCities.empty()) return "";
        return usedCities.back();
    }

    // Методы для работы с игроками
    void AddPlayer(const std::string& playerName) {
        if (playerName.empty()) return;
        players.push_back(playerName);
    }

    int GetPlayersCount() const {
        return players.size();
    }

    std::string GetCurrentPlayer() const {
        if (players.empty()) return "";
        return players[currentPlayerIndex];
    }

    void NextPlayer() {
        if (players.empty()) return;
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    }

    void ResetPlayers() {
        currentPlayerIndex = 0;
    }

    const std::vector<std::string>& GetPlayers() const {
        return players;
    }

    int GetCurrentPlayerIndex() const {
        return currentPlayerIndex;
    }

    int GetUsedCitiesCount() const {
        return usedCities.size();
    }

    void ResetGame() {
        usedCities.clear();
    }

    // Перегруженная версия AddCity с проверкой правила последней буквы
    bool AddCity(const std::string& city, const std::string& lastCity) {
        if (!IsCityExist(city)) return false;
        if (IsCityUsed(city)) return false;
        if (!IsValidNextCity(lastCity, city) && !lastCity.empty()) return false;

        usedCities.push_back(city);
        return true;
    }
};

// Определяем статическую константу вне класса
const std::string Game::FORBIDDEN_LETTERS = "ъыьЪЫЬ";