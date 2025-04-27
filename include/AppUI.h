#ifndef APPUI_H
#define APPUI_H

#include "WeatherClient.h"

class AppUI {
  public:
    void run();

  private:
    void printWeather(const WeatherData& weather);
    void printAirQuality(const AirQualityData& airQuality);
};

#endif //APPUI_H
