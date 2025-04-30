#include "AppUI.h"
#include <iostream>
#include <iomanip> // for std::setw

void AppUI::run() {
    WeatherClient client;
    std::string city;

    std::cout << std::setw(14) << std::left << "\n========== WELCOME TO THE WEATHER REPORT ==========\n";

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
            printReport(weather, airQuality);
        } catch (const std::exception& e) {
            std::cout << "\nError: " << e.what() << "\n";
        }
    }
}

// print weather report
void AppUI::printReport(const WeatherData& weather, const AirQualityData& airQuality) {
    std::cout << "\n========== Current Weather for " << weather.location << ", " << weather.country << " ==========\n";
    std::cout << "\n";
    std::cout << std::setw(14) << std::left << "Temperature" << " | " << weather.tempC << "°C / " << weather.tempF << "°F\n";
    std::cout << std::setw(14) << std::left << "Condition" << " | " << weather.condition << "\n";
    std::cout << std::setw(14) << std::left << "Wind" << " | " << weather.windKph << "kph / " << weather.windMph << "mph\n";
    std::cout << std::setw(14) << std::left << "Humidity" << " | " << weather.humidity << "%\n";

    if (airQuality.epaIndex != -1) {
        std::cout << std::setw(14) << std::left << "Air Quality" << " | " << airQuality.epaCategory << "\n";
    } else {
        std::cout << "\nAir quality data not available.\n";
    }
}


