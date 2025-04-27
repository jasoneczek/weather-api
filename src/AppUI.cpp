#include "AppUI.h"
#include <iostream>

void AppUI::run() {
    std::string city;

    std::cout << "Enter city name: ";
    std::getline(std::cin, city);

    try {
        WeatherClient client;
        auto [weather, airQuality] = client.getWeather(city);

        // print weather and air quaility data
        printWeather(weather);
        printAirQuality(airQuality);
    } catch (const std::exception& e) {
      std::cerr << "Error: " << e.what() << "\n";
    }
}

// *********************************
// HELPER FUNCTIONS FOR PRINTING DATA
// *********************************

void AppUI::printWeather(const WeatherData& weather) {
    std::cout << "\n*************************************\n";
    std::cout << "Current Weather for " << weather.location << ", " << weather.country << ":\n";
    std::cout << "Temperature: " << weather.tempC << "°C / " << weather.tempF << "°F\n";
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
