#ifndef BOOSTHTTPCLIENT_H
#define BOOSTHTTPCLIENT_H

#include "HttpClient.h"

class BoostHttpClient : public HttpClient {
  public:
    void makeRequest() override;
};

#endif //BOOSTHTTPCLIENT_H
