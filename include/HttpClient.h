#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <string>

class HttpClient {
  public:
    virtual void makeRequest(const std::string& host, const std::string& target) = 0;
    virtual ~HttpClient() = default;
};

#endif //HTTPCLIENT_H
