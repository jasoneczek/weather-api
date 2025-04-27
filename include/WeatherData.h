#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include "JsonExtractable.h"
#include <string>

// stores current weather info from JSON response
// inherited from JsonExtractable class
class WeatherData final : public JsonExtractable {
  public:
    std::string location;
    std::string country;
    double tempC = 0.0;
    double tempF = 0.0;
    std::string condition;
    double windKph = 0.0;
    double windMph = 0.0;
    int humidity = 0;

    // extracts weather fields from JSON object
    void extractFromJson(const json& parsed) override;
};

#endif //WEATHERDATA_H
