#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <nlohmann/json.hpp>

class JsonParser {
  public:
    static nlohmann::json parse(const std::string &jsonResponse);
};

#endif //JSONPARSER_H
