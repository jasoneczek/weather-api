#include "WeatherClient.h"
#include "Config.h"
#include "JsonParser.h"
#include <iostream>

std::pair<WeatherData, AirQualityData> WeatherClient::getWeather(std::string& city) {
  // create empty WeatherData and AirQualityData objects
  // to fill from the API response
  WeatherData weather;
  AirQualityData airQuality;

  std::string apiKey = getApiKey();
  if (apiKey.empty()) {
    throw std::runtime_error("API Key is empty");
  }

  const std::string host = "api.weatherapi.com";
  const std::string target = buildTarget(apiKey, city);

  const std::string response = httpClient.makeRequest(host, target);

  try {
    json parsed = parseJson(response);

    // Check if API returned an error
    if (parsed.contains("error")) {
      int errorCode = parsed["error"]["code"].get<int>();
      auto errorMessage = parsed["error"]["message"].get<std::string>();

      throw std::runtime_error(
        "API Error (HTTP 400, Code "+ std::to_string(errorCode) + "): " + errorMessage);
    }

    weather.extractFromJson(parsed);
    airQuality.extractFromJson(parsed);

  } catch (const std::exception &e) {
    throw;
  }
  return {weather, airQuality}; // return data together as pair
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
  std::string encodedCity = urlEncode(city); // added to encode city before building target
  return "/v1/current.json?key=" + apiKey + "&q=" + encodedCity + "&aqi=yes";
}

// url encode city names to handle spaces
std::string WeatherClient::urlEncode(const std::string& str) {
  std::string encoded;
  for (const char c : str) {
    if (c == ' ') {
      encoded += "%20";
    } else {
      encoded += c;
    }
  }
  return encoded;
}