#include "WeatherClient.h"
#include "Config.h"
#include "JsonParser.h"
#include <iostream>

using json = nlohmann::json;

void WeatherClient::getWeather() {
  std::string apiKey = Config::getApiKey();
  if (apiKey.empty()) {
    std::cerr << "API Key not found" << std::endl;
    return;
  }

  // temporary hardcoded city name request for testing
  std::string host = "api.weatherapi.com";
  std::string city = "Opole";
  std::string target = "/v1/current.json?key=" + apiKey + "&q=" + city + "&aqi=yes";

  std::string response = httpClient.makeRequest(host, target);

  try {
    auto parsed = parseJson(response);
    std::cout << parsed.dump(2) << std::endl; // pretty print full json response for testing

  } catch (const std::exception &e) {
    std::cerr << "Error parsing json: " << e.what() << std::endl;
  }
}

// HELPER FUNCTIONS

// get api key
std::string WeatherClient::getApiKey() {
  return Config::getApiKey();
}

// parse JSON
json WeatherClient::parseJson(const std::string& response) {
  return JsonParser::parse(response);
}