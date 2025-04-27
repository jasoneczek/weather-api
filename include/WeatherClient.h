#ifndef WEATHERCLIENT_H
#define WEATHERCLIENT_H

#include "BoostHttpClient.h"
#include <nlohmann/json.hpp>
#include <string>

class WeatherClient {
  public:
    void getWeather(std::string& city); // added city parameter to accept user input

  private:
    BoostHttpClient httpClient;

  // changed above 2 methods to static because they don't rely on instance data
    static std::string getApiKey();
      // doesn't read from httpClient
      // doesn't matter what city is passed in
      // doesn't store or update variables
    static nlohmann::json parseJson(const std::string& response);
      // only takes input response and returns parsed JSON
      // doesn't rely on WeatherClient object
    std::string buildTarget(const std::string& apiKey, const std::string& city);
};

#endif //WEATHERCLIENT_H
