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
    std::string location = parsed["location"]["name"].get<std::string>();
    std::string country = parsed["location"]["country"].get<std::string>();
    double tempC = parsed["current"]["temp_c"].is_number() ? parsed["current"]["temp_c"].get<double>() : 0.0;
    double tempF = parsed["current"]["temp_f"].is_number() ? parsed["current"]["temp_f"].get<double>() : 0.0;

    std::cout << "Weather for " << location << ", " << country << ":\n";
    std::cout << "Temperature: " << tempC << "°C / " << tempF << "°F\n";

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