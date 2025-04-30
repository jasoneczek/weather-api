#ifndef APPUI_H
#define APPUI_H

#include "WeatherClient.h"

class AppUI {
  public:
    void run();

  private:
    void printReport(const WeatherData& weather, const AirQualityData& airQuality);
};

#endif //APPUI_H
