#ifndef WEATHERCLIENT_H
#define WEATHERCLIENT_H

#include "BoostHttpClient.h"

class WeatherClient {
  public:
    void getWeather();

  private:
    BoostHttpClient httpClient;
};

#endif //WEATHERCLIENT_H
