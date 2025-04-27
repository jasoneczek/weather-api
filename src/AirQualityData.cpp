#include "AirQualityData.h"

void AirQualityData::extractFromJson(const json& parsed) {
    if (parsed["current"].contains("air_quality")) {
        const auto& air = parsed["current"]["air_quality"];

        epaIndex = air.contains("us-epa-index")
            && air["us-epa-index"].is_number_integer()
            ? air["us-epa-index"].get<int>()
            : -1;

        switch (epaIndex) {
            case 1: epaCategory = "Good"; break;
            case 2: epaCategory = "Moderate"; break;
            case 3: epaCategory = "Unhealthy for Sensitive Groups"; break;
            case 4: epaCategory = "Unhealthy"; break;
            case 5: epaCategory = "Very Unhealthy"; break;
            case 6: epaCategory = "Hazardous"; break;
            default: epaCategory = "Unknown"; break; // if air quality not available
        }
    } else {
        epaIndex = -1;
        epaCategory = "Unknown";
    }
}
