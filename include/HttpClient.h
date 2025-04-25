#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

class HttpClient {
  public:
    virtual void makeRequest() = 0;
    virtual ~HttpClient() = default;
};

#endif //HTTPCLIENT_H
