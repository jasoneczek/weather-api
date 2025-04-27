#ifndef AIRQUALITYDATA_H
#define AIRQUALITYDATA_H

#include "JsonExtractable.h"
#include <string>

class AirQualityData final : public JsonExtractable {
public:
  int epaIndex = -1;
  std::string epaCategory = "Unknown";

  void extractFromJson(const json &parsed) override;
};

#endif //AIRQUALITYDATA_H
