#include "AppUI.h"
#include <iostream>

void AppUI::run() {
    WeatherClient client;
    std::string city;

    while (true) {
        std::cout << "\nEnter city name (or 0 to exit): ";
        std::getline(std::cin, city);

        if (city == "0") {
            std::cout << "Goodbye!\n";
            break;
        }

        if (city.empty()) {
          std::cout << "Please enter a city name.\n";
          continue;
        }

        try {
            auto [weather, airQuality] = client.getWeather(city);
            printWeather(weather);
            printAirQuality(airQuality);
        } catch (const std::exception& e) {
            std::cout << "\nError: " << e.what() << "\n";
        }
        std::cout << "\n=========================================\n";
    }
}

// *********************************
// HELPER FUNCTIONS FOR PRINTING DATA
// *********************************

void AppUI::printWeather(const WeatherData& weather) {
    std::cout << "\n=========================================\n";
    std::cout << "\nCurrent Weather for " << weather.location << ", " << weather.country << ":\n";
    std::cout << "\nTemperature: " << weather.tempC << "°C / " << weather.tempF << "°F\n";
    std::cout << "Condition: " << weather.condition << "\n";
    std::cout << "Wind: " << weather.windKph << "kph / " << weather.windMph << "mph\n";
    std::cout << "Humidity: " << weather.humidity << "%\n";
}

void AppUI::printAirQuality(const AirQualityData& airQuality) {
    if (airQuality.epaIndex != -1) {
        std::cout << "Air Quality: " << airQuality.epaCategory << "\n";
    } else {
        std::cout << "\nAir quality data not available.\n";
    }
}

