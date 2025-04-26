#ifndef WEATHERCLIENT_H
#define WEATHERCLIENT_H

#include "BoostHttpClient.h"
#include <nlohmann/json.hpp>
#include <string>

class WeatherClient {
  public:
    void getWeather();

  private:
    BoostHttpClient httpClient;
    std::string getApiKey();
    nlohmann::json parseJson(const std::string& response);
};

#endif //WEATHERCLIENT_H
