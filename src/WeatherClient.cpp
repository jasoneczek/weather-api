#include "WeatherClient.h"
#include "Config.h"
#include "JsonParser.h"
#include <iostream>

using json = nlohmann::json;

void WeatherClient::getWeather(std::string& city) {
  std::string apiKey = Config::getApiKey();
  if (apiKey.empty()) {
    std::cerr << "API Key not found" << std::endl;
    return;
  }

  const std::string host = "api.weatherapi.com";
  const std::string target = buildTarget(apiKey, city);

  const std::string response = httpClient.makeRequest(host, target);

  try {
    auto parsed = parseJson(response);

    // extracting fields from JSON into local variables for now
    // will refactor into Weather struct later

    // matching field names and types from https://www.weatherapi.com/docs

    // WEATHER FIELDS
    auto location = parsed["location"]["name"].get<std::string>();
    auto country = parsed["location"]["country"].get<std::string>();
    double tempC = parsed["current"]["temp_c"].is_number() ? parsed["current"]["temp_c"].get<double>() : 0.0;
    double tempF = parsed["current"]["temp_f"].is_number() ? parsed["current"]["temp_f"].get<double>() : 0.0;
    auto condition = parsed["current"]["condition"]["text"].get<std::string>();
    double windKph = parsed["current"]["wind_kph"].is_number() ? parsed["current"]["wind_kph"].get<double>() : 0.0;
    double windMph = parsed["current"]["wind_mph"].is_number() ? parsed["current"]["wind_mph"].get<double>() : 0.0;
    int humidity = parsed["current"]["humidity"].is_number() ? parsed["current"]["humidity"].get<int>() : 0;

    std::cout << "Weather for " << location << ", " << country << ":\n";
    std::cout << "Temperature: " << tempC << "°C / " << tempF << "°F\n";
    std::cout << "Condition: " << condition << "\n";
    std::cout << "Wind: " << windKph << "kph / " << windMph << "mph\n";
    std::cout << "Humidity: " << humidity << "%\n";

    // AIR QUALITY FIELDS
    // check if air quality is available
    if (parsed["current"].contains("air_quality")) {
      const auto& air = parsed["current"]["air_quality"];

      int epaIndex = air.contains("us-epa-index")
          && air["us-epa-index"].is_number_integer()
          ? air["us-epa-index"].get<int>()
          : -1;

      std::string epaCategory;
      switch (epaIndex) {
        case 1: epaCategory = "Good"; break;
        case 2: epaCategory = "Moderate"; break;
        case 3: epaCategory = "Unhealthy for Sensitive Groups"; break;
        case 4: epaCategory = "Unhealthy"; break;
        case 5: epaCategory = "Very Unhealthy"; break;
        case 6: epaCategory = "Hazardous"; break;
        default: epaCategory = "Unknown"; break; // if air quality not available
      }

      std::cout << "Air Quality: " << epaCategory << "\n";
    } else {
      std::cout << "Air quality data not available.\n";
    }

  } catch (const std::exception &e) {
    std::cerr << "Error parsing json: " << e.what() << std::endl;
  }
}

// ****************************
// HELPER FUNCTIONS
// ****************************

// get api key
std::string WeatherClient::getApiKey() {
  return Config::getApiKey();
}

// parse JSON
json WeatherClient::parseJson(const std::string& response) {
  return JsonParser::parse(response);
}

// build target - added in case I add more user options like forecast and history later
std::string WeatherClient::buildTarget(const std::string& apiKey, const std::string& city) {
  return "/v1/current.json?key=" + apiKey + "&q=" + city + "&aqi=yes";
}