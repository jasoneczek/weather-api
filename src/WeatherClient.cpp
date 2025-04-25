#include "WeatherClient.h"
#include "Config.h"
#include <iostream>
#include <nlohmann/json.hpp>

#include <cstdlib>

using json = nlohmann::json;

void WeatherClient::getWeather() {
  std::string apiKey = Config::getApiKey();
  if (apiKey.empty()) {
    std::cerr << "API Key not found" << std::endl;
    return;
  }

  std::string host = "api.weatherapi.com";
  std::string city = "Opole";
  std::string target = "/v1/current.json?key=" + apiKey + "&q=" + city + "&aqi=yes";

  httpClient.makeRequest(host, target);
}
