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
    };
}