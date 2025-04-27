#include "WeatherClient.h"
#include <iostream>

int main() {
    std::string city;

    std::cout << "Enter city name: ";

    std::getline(std::cin, city);

    // create WeatherClient object
    WeatherClient client;
    // fetch data for the city and unpack into 2 objects
    // auto automatically figures out the types
    // results are split into weather and airQuality
    auto [weather, airQuality] = client.getWeather(city);

    std::cout << "\n*************************************\n";
    std::cout << "Current Weather for " << weather.location << ", " << weather.country << ":\n";
    std::cout << "Temperature: " << weather.tempC << "°C / " << weather.tempF << "°F\n";
    std::cout << "Condition: " << weather.condition << "\n";
    std::cout << "Wind: " << weather.windKph << "kph / " << weather.windMph << "mph\n";
    std::cout << "Humidity: " << weather.humidity << "%\n";

    if (airQuality.epaIndex != -1) {
        std::cout << "Air Quality: " << airQuality.epaCategory << "\n";
    } else {
    std::cout << "\nAir quality data not available.\n";
}

    return 0;
}