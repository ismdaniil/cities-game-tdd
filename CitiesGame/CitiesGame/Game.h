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
    std::vector<std::string> citiesDatabase;  // База допустимых городов
    std::vector<std::string> usedCities;      // Уже названные города
    std::vector<std::string> players;          // Список игроков
    int currentPlayerIndex = 0;                // Индекс текущего игрока
    static const std::string FORBIDDEN_LETTERS; // Буквы, которые пропускаем

    /**
     * Приводит русскую или английскую букву к нижнему регистру
     * @param c исходный символ
     * @return символ в нижнем регистре
     */
    char ToLowerRussian(char c) const {
        // Русские заглавные буквы (диапазон А-Я в CP1251)
        if (c >= 'А' && c <= 'Я') {
            return c + 32; // Смещение до строчных букв
        }
        // Английские заглавные буквы
        if (c >= 'A' && c <= 'Z') {
            return c + 32; // Смещение до строчных
        }
        return c; // Уже строчная или не буква
    }

public:
    const std::vector<std::string>& GetUsedCities() const {
        return usedCities;
    }
    /**
     * Загружает базу допустимых городов
     * @param database вектор с названиями городов
     */
    void LoadDatabase(const std::vector<std::string>& database) {
        if (database.empty()) {
            citiesDatabase.clear();
            return;
        }
        citiesDatabase = database;
    }
    /**
 * Возвращает первый названный город
 * @return первый город или пустую строку, если городов нет
 */
    std::string GetFirstUsedCity() const {
        if (usedCities.empty()) {
            return "";
        }
        return usedCities.front(); // используем front() вместо [0] для ясности
    }
    /**
     * Проверяет, существует ли город в базе
     * @param city название города
     * @return true если город есть в базе
     */
    bool IsCityExist(const std::string& city) const {
        return std::find(citiesDatabase.begin(), citiesDatabase.end(), city) != citiesDatabase.end();
    }
    /**
 * Проверяет, не названо ли еще ни одного города
 * @return true если список использованных городов пуст
 */
    bool IsUsedCitiesEmpty() const {
        return usedCities.empty();
    }
    /**
     * Получает последнюю значимую букву города (пропуская Ъ, Ы, Ь)
     * @param city название города
     * @return последняя значимая буква в нижнем регистре
     */
    char GetLastSignificantChar(const std::string& city) const {
        if (city.empty()) return '\0';

        // Ищем с конца первый символ, не являющийся запрещенным
        for (int i = city.length() - 1; i >= 0; i--) {
            char currentChar = city[i];
            if (FORBIDDEN_LETTERS.find(currentChar) == std::string::npos) {
                return ToLowerRussian(currentChar);
            }
        }

        // Если все символы запрещенные (редкий случай)
        return ToLowerRussian(city.back());
    }

    /**
     * Проверяет, подходит ли следующий город по правилу последней буквы
     * @param lastCity предыдущий город
     * @param nextCity следующий город
     * @return true если правило соблюдено
     */
    bool IsValidNextCity(const std::string& lastCity, const std::string& nextCity) const {
        if (lastCity.empty() || nextCity.empty()) return true;

        char lastChar = GetLastSignificantChar(lastCity);
        char firstChar = ToLowerRussian(nextCity[0]);

        return lastChar == firstChar;
    }

    /**
     * Добавляет город в список использованных
     * @param city название города
     * @return true если город успешно добавлен
     */
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

    /**
     * Проверяет, был ли город уже использован
     * @param city название города
     * @return true если город уже называли
     */
    bool IsCityUsed(const std::string& city) const {
        return std::find(usedCities.begin(), usedCities.end(), city) != usedCities.end();
    }

    /**
     * Возвращает последний использованный город
     * @return название последнего города или пустую строку
     */
    std::string GetLastCity() const {
        if (usedCities.empty()) return "";
        return usedCities.back();
    }

    /**
     * Добавляет игрока
     * @param playerName имя игрока
     */
    void AddPlayer(const std::string& playerName) {
        if (playerName.empty()) return;
        players.push_back(playerName);
    }

    /**
     * Возвращает количество игроков
     * @return число игроков
     */
    int GetPlayersCount() const {
        return players.size();
    }

    /**
     * Возвращает имя текущего игрока
     * @return имя игрока или пустую строку
     */
    std::string GetCurrentPlayer() const {
        if (players.empty()) return "";
        return players[currentPlayerIndex];
    }

    /**
     * Переходит к следующему игроку
     */
    void NextPlayer() {
        if (players.empty()) return;
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    }

    /**
     * Сбрасывает очередь игроков к первому
     */
    void ResetPlayers() {
        currentPlayerIndex = 0;
    }

    /**
     * Возвращает список всех игроков
     * @return константная ссылка на вектор игроков
     */
    const std::vector<std::string>& GetPlayers() const {
        return players;
    }

    /**
     * Возвращает индекс текущего игрока
     * @return индекс (0-based)
     */
    int GetCurrentPlayerIndex() const {
        return currentPlayerIndex;
    }

    /**
     * Возвращает количество использованных городов
     * @return число названных городов
     */
    int GetUsedCitiesCount() const {
        return usedCities.size();
    }

    /**
     * Сбрасывает игру (очищает список использованных городов)
     */
    void ResetGame() {
        usedCities.clear();
    }

    /**
     * Добавляет город с проверкой правила последней буквы
     * @param city новый город
     * @param lastCity предыдущий город
     * @return true если город успешно добавлен
     */
    bool AddCity(const std::string& city, const std::string& lastCity) {
        if (!IsCityExist(city)) return false;
        if (IsCityUsed(city)) return false;
        if (!IsValidNextCity(lastCity, city) && !lastCity.empty()) return false;

        usedCities.push_back(city);
        return true;
    }
    bool RemovePlayer(const std::string& playerName) {
        auto it = std::find(players.begin(), players.end(), playerName);
        if (it != players.end()) {
            int index = it - players.begin();
            players.erase(it);

            // Корректируем индекс текущего игрока
            if (index < currentPlayerIndex) {
                currentPlayerIndex--;
            }
            else if (currentPlayerIndex >= static_cast<int>(players.size()) && !players.empty()) {
                currentPlayerIndex = 0;
            }
            return true;
        }
        return false;
    }
    std::string GetNextPlayer() const {
        if (players.empty()) return "";
        int nextIndex = (currentPlayerIndex + 1) % players.size();
        return players[nextIndex];
    }
};

// Определение статической константы
const std::string Game::FORBIDDEN_LETTERS = "ъыьЪЫЬ";