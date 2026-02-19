#include "pch.h"
#include "CppUnitTest.h"
#include "../CitiesGame/Timer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CitiesGameTests
{
    TEST_CLASS(TimerTests)
    {
    public:
        TEST_METHOD(Timer_Start_NotExpiredImmediately)
        {
            // Arrange
            Timer timer;

            // Act
            timer.Start(5);

            // Assert
            Assert::IsFalse(timer.IsExpired());
        }
        TEST_METHOD(Timer_GetRemainingTime_JustStarted_ReturnsFullTime)
        {
            // Arrange
            Timer timer;

            // Act
            timer.Start(5);

            // Assert
            Assert::AreEqual(5, timer.GetRemainingTime());
        }
        TEST_METHOD(Timer_Stop_TimerExpired)
        {
            // Arrange
            Timer timer;
            timer.Start(5);

            // Act
            timer.Stop(); 

            // Assert
            Assert::IsTrue(timer.IsExpired());
        }
        TEST_METHOD(Timer_Wait_WaitsAtLeastSpecifiedTime)
        {
            // Arrange
            auto start = std::chrono::steady_clock::now();

            // Act
            Timer::Wait(1); // щрнцн лерндю мер!

            // Assert
            auto end = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            Assert::IsTrue(elapsed.count() >= 1000);
        }
    };
}