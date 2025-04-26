#include "JsonParser.h"
#include <iostream>

nlohmann::json JsonParser::parse(const std::string &jsonResponse) {
  try {
    return nlohmann::json::parse(jsonResponse);
  } catch (const nlohmann::json::parse_error &e) {
    std::cerr << "Error parsing json: " << e.what() << std::endl;
    throw;
  }
}