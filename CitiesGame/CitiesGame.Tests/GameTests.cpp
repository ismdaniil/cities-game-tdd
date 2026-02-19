#include "pch.h"
#include "CppUnitTest.h"
#include "../CitiesGame/Game.h" // Подключаем будущий класс

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CitiesGameTests
{
    TEST_CLASS(GameTests)
    {
    public:
        TEST_METHOD(IsCityExist_CityInDatabase_ReturnsTrue)
        {
            // Arrange
            Game game;
            std::string city = "Москва";

            // Act
            bool result = game.IsCityExist(city);

            // Assert
            Assert::IsTrue(result);
        }
    };
}
