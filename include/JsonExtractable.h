#ifndef JSONEXTRACTABLE_H
#define JSONEXTRACTABLE_H

#include <nlohmann/json.hpp>

using json = nlohmann::json;

// abstract class so that any object can extract data from a JSON structure
class JsonExtractable {
  public:
    // pure virtual function to extract fields from a parsed JSON object
    virtual void extractFromJson(const json& parsed) = 0;
    virtual ~JsonExtractable() = default;
};

#endif //JSONEXTRACTABLE_H
