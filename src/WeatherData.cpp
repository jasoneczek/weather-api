#include "WeatherData.h"

void WeatherData::extractFromJson(const json& parsed) {
    location = parsed["location"]["name"].get<std::string>();
    country = parsed["location"]["country"].get<std::string>();
    tempC = parsed["current"]["temp_c"].is_number() ? parsed["current"]["temp_c"].get<double>() : 0.0;
    tempF = parsed["current"]["temp_f"].is_number() ? parsed["current"]["temp_f"].get<double>() : 0.0;
    condition = parsed["current"]["condition"]["text"].get<std::string>();
    windKph = parsed["current"]["wind_kph"].is_number() ? parsed["current"]["wind_kph"].get<double>() : 0.0;
    windMph = parsed["current"]["wind_mph"].is_number() ? parsed["current"]["wind_mph"].get<double>() : 0.0;
    humidity = parsed["current"]["humidity"].is_number() ? parsed["current"]["humidity"].get<int>() : 0;
}