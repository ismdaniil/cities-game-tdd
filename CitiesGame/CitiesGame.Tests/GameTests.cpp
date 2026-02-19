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
            std::vector<std::string> testDatabase = { "Москва" }; // Создаем тестовую базу
            game.LoadDatabase(testDatabase); // Загружаем ее
            std::string city = "Москва";

            // Act
            bool result = game.IsCityExist(city);

            // Assert
            Assert::IsTrue(result);
        }
        TEST_METHOD(IsCityExist_AfterLoadingDatabase_ReturnsTrueForNewCity)
        {
            // ARRANGE - готовим данные
            Game game;
            std::vector<std::string> testDatabase = { "Париж", "Лондон", "Токио" };
            game.LoadDatabase(testDatabase); // ЭТОГО МЕТОДА ПОКА НЕТ - тест не скомпилируется (КРАСНЫЙ)
            std::string city = "Лондон";

            // ACT - выполняем действие
            bool result = game.IsCityExist(city);

            // ASSERT - проверяем результат
            Assert::IsTrue(result);
        }
    };

}
