#include "WeatherClient.h"
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void WeatherClient::getWeather() {
  httpClient.makeRequest();
}
