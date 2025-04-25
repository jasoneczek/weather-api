#include "Config.h"
#include <cstdlib>

std::string Config::getApiKey() {
  const char* apiKey = std::getenv("WEATHER_API_KEY");
  return apiKey ? std::string(apiKey) : std::string("");
}
