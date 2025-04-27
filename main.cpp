#include "WeatherClient.h"
#include <iostream>
#include <string>

int main() {
    std::string city;

    std::cout << "Enter city name: ";

    std::getline(std::cin, city);

    WeatherClient weather;
    weather.getWeather(city);

    return 0;
}