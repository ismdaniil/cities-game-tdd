#pragma once
#include <chrono>
#include <thread>

class Timer {
private:
    std::chrono::steady_clock::time_point startTime;
    int durationSeconds;
    bool isRunning;

public:
    Timer() : startTime(), durationSeconds(0), isRunning(false) {}

    static void Wait(int seconds) {
        std::this_thread::sleep_for(std::chrono::seconds(seconds));
    }
    /**
 * Останавливает таймер
 */
    void Stop() {
        isRunning = false;
    }
    /**
    * Возвращает количество оставшихся секунд
    * @return оставшееся время в секундах (0 если время истекло)
    */
    int GetRemainingTime() const {
        if (!isRunning) return 0;

        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime);
        int remaining = durationSeconds - static_cast<int>(elapsed.count());

        return (remaining > 0) ? remaining : 0;
    }
    /**
     * Запускает таймер на указанное количество секунд
     * @param seconds количество секунд
     */
    void Start(int seconds) {
        durationSeconds = seconds;
        startTime = std::chrono::steady_clock::now();
        isRunning = true;
    }

    /**
     * Проверяет, истекло ли время
     * @return true если время истекло или таймер не запущен
     */
    bool IsExpired() const {
        if (!isRunning) return true;
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime);
        return elapsed.count() >= durationSeconds;
    }
};