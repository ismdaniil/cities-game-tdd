#pragma once
#include <chrono>

class Timer {
private:
    std::chrono::steady_clock::time_point startTime;
    int durationSeconds;
    bool isRunning;

public:
    Timer() : durationSeconds(0), isRunning(false) {}

    void Start(int seconds) {
        durationSeconds = seconds;
        startTime = std::chrono::steady_clock::now();
        isRunning = true;
    }

    bool IsExpired() const {
        if (!isRunning) return true;
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime);
        return elapsed.count() >= durationSeconds;
    }
};