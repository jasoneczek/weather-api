#ifndef WEATHERCLIENT_H
#define WEATHERCLIENT_H

#include "BoostHttpClient.h"
#include "WeatherData.h"
#include "AirQualityData.h"
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

// WeatherClient is responsible for fetching weather and air quality data from weatherapi
class WeatherClient {
  public:
    // returns pair of objects: WeatherData and AirQualityData
    std::pair<WeatherData, AirQualityData> getWeather(std::string& city);

  private:
    BoostHttpClient httpClient; // HTTP client for sending requests

    static std::string getApiKey(); // retrieves api key from env variable
    static json parseJson(const std::string& response); // parson JSON response string into JSON object
    static std::string buildTarget(const std::string& apiKey, const std::string& city); // builds url

    // helper function to encode city names with spaces ex. New York
    static std::string urlEncode(const std::string& str);
};

#endif //WEATHERCLIENT_H
