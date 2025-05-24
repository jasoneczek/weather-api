#include "AirQualityData.h"
#include "utils/Colors.h"

void AirQualityData::extractFromJson(const json& parsed) {
    if (parsed["current"].contains("air_quality")) {
        const auto& air = parsed["current"]["air_quality"];

        epaIndex = air.contains("us-epa-index")
            && air["us-epa-index"].is_number_integer()
            ? air["us-epa-index"].get<int>()
            : -1;

        switch (epaIndex) {
            case 1: epaCategory = GOOD "Good" RESET; break;
            case 2: epaCategory = MODERATE "Moderate" RESET; break;
            case 3: epaCategory = MODERATE "Unhealthy for Sensitive Groups" RESET; break;
            case 4: epaCategory = UNHEALTHY "Unhealthy" RESET; break;
            case 5: epaCategory = UNHEALTHY "Very Unhealthy" RESET; break;
            case 6: epaCategory = UNHEALTHY "Hazardous" RESET; break;
            default: epaCategory = UNKNOWN "Unknown" RESET; break; // if air quality not available
        }
    } else {
        epaIndex = -1;
        epaCategory = "Unknown";
    }
}
