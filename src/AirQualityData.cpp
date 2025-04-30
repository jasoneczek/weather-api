#include "AirQualityData.h"

void AirQualityData::extractFromJson(const json& parsed) {
    if (parsed["current"].contains("air_quality")) {
        const auto& air = parsed["current"]["air_quality"];

        epaIndex = air.contains("us-epa-index")
            && air["us-epa-index"].is_number_integer()
            ? air["us-epa-index"].get<int>()
            : -1;

        switch (epaIndex) {
            case 1: epaCategory = "\033[92mGood\033[0m"; break;
            case 2: epaCategory = "\033[93mModerate\033[0m"; break;
            case 3: epaCategory = "\033[93mUnhealthy for Sensitive Groups\033[0m"; break;
            case 4: epaCategory = "\033[91mUnhealthy\033[0m"; break;
            case 5: epaCategory = "\033[91mVery Unhealthy\033[0m"; break;
            case 6: epaCategory = "\033[91mHazardous\033[0m"; break;
            default: epaCategory = "\033[90mUnknown\033[0m"; break; // if air quality not available
        }
    } else {
        epaIndex = -1;
        epaCategory = "Unknown";
    }
}
