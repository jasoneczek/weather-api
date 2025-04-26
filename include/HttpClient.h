#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <string>

class HttpClient {
  public:
    virtual std::string makeRequest(const std::string& host, const std::string& target) = 0; // now returns a string
    virtual ~HttpClient() = default;
};

#endif //HTTPCLIENT_H
