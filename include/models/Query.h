#ifndef QUERY_H
#define QUERY_H

#include <string>

class Query {
  public:
    int id;
    std::string city;
    std::string timestamp;

    Query(int id, const std::string& city, const std::string& timestamp)
        : id(id), city(city), timestamp(timestamp) {}
};

#endif //QUERY_H
