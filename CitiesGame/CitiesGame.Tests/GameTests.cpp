#include "pch.h"
#include "CppUnitTest.h"
#include "../CitiesGame/Game.h"

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
            game.LoadDatabase(testDatabase); 
            std::string city = "Лондон";

            // ACT - выполняем действие
            bool result = game.IsCityExist(city);

            // ASSERT - проверяем результат
            Assert::IsTrue(result);
        }
        TEST_METHOD(GetLastSignificantChar_NormalCity_ReturnsLastChar)
        {
            // Arrange
            Game game;
            std::string city = "Москва";

            // Act
            char result = game.GetLastSignificantChar(city);

            // Assert
            Assert::AreEqual('а', result);
        }

        TEST_METHOD(GetLastSignificantChar_CityEndsWithSoftSign_ReturnsPreviousChar)
        {
            // Arrange
            Game game;
            std::string city = "Харьков"; // Заканчивается на 'в' после 'ь'

            // Act
            char result = game.GetLastSignificantChar(city);

            // Assert
            Assert::AreEqual('в', result);
        }

        TEST_METHOD(GetLastSignificantChar_CityEndsWithHardSign_ReturnsPreviousChar)
        {
            // Arrange
            Game game;
            std::string city = "Подъезд"; // Заканчивается на 'д' после 'ъ'

            // Act
            char result = game.GetLastSignificantChar(city);

            // Assert
            Assert::AreEqual('д', result);
        }

        TEST_METHOD(IsValidNextCity_ValidCity_ReturnsTrue)
        {
            // Arrange
            Game game;
            std::string lastCity = "Москва";  // Заканчивается на 'а'
            std::string nextCity = "Архангельск"; // Начинается на 'А'

            // Act
            bool result = game.IsValidNextCity(lastCity, nextCity);

            // Assert
            Assert::IsTrue(result);
        }

        TEST_METHOD(IsValidNextCity_InvalidCity_ReturnsFalse)
        {
            // Arrange
            Game game;
            std::string lastCity = "Москва";  // Заканчивается на 'а'
            std::string nextCity = "Брянск";   // Начинается на 'Б'

            // Act
            bool result = game.IsValidNextCity(lastCity, nextCity);

            // Assert
            Assert::IsFalse(result);
        }

        TEST_METHOD(IsValidNextCity_WithSoftSign_ReturnsTrue)
        {
            // Arrange
            Game game;
            std::string lastCity = "Харьков";  // Значимая последняя буква 'в'
            std::string nextCity = "Воронеж";   // Начинается на 'В'

            // Act
            bool result = game.IsValidNextCity(lastCity, nextCity);

            // Assert
            Assert::IsTrue(result);
        }
       
        TEST_METHOD(GetUsedCities_AfterAddingCity_ReturnsVectorWithCity)
        {
            // Arrange
            Game game;
            std::vector<std::string> testDatabase = { "Москва" };
            game.LoadDatabase(testDatabase);
            game.AddCity("Москва");

            // Act
            std::vector<std::string> usedCities = game.GetUsedCities(); 

            // Assert
            Assert::AreEqual(std::string("Москва"), usedCities[0]);
        }
        TEST_METHOD(IsUsedCitiesEmpty_NoCitiesAdded_ReturnsTrue)
        {
            // Arrange
            Game game;

            // Act
            bool result = game.IsUsedCitiesEmpty();

            // Assert
            Assert::IsTrue(result);
        }
        TEST_METHOD(GetFirstUsedCity_AfterAddingTwoCities_ReturnsFirstCity)
        {
            // Arrange
            Game game;
            std::vector<std::string> testDatabase = { "Москва", "Минск", "Киев" };
            game.LoadDatabase(testDatabase);
            game.AddCity("Москва");
            game.AddCity("Минск");
            game.AddCity("Киев");

            // Act
            std::string firstCity = game.GetFirstUsedCity(); 

            // Assert
            Assert::AreEqual(std::string("Москва"), firstCity);
        }
        TEST_METHOD(RemovePlayer_ExistingPlayer_ReturnsTrue)
        {
            // Arrange
            Game game;
            game.AddPlayer("Алиса");
            game.AddPlayer("Боб");

            // Act
            bool result = game.RemovePlayer("Алиса"); 

            // Assert
            Assert::IsTrue(result);
        }
        TEST_METHOD(GetNextPlayer_AfterFirstPlayer_ReturnsSecondPlayer)
        {
            // Arrange
            Game game;
            game.AddPlayer("Алиса");
            game.AddPlayer("Боб");

            // Act
            std::string nextPlayer = game.GetNextPlayer();

            // Assert
            Assert::AreEqual(std::string("Боб"), nextPlayer);
        }
        TEST_METHOD(HasPlayer_ExistingPlayer_ReturnsTrue)
        {
            // Arrange
            Game game;
            game.AddPlayer("Алиса");

            // Act
            bool result = game.HasPlayer("Алиса");

            // Assert
            Assert::IsTrue(result);
        }
    };

}
