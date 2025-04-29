#ifndef BOOSTHTTPCLIENT_H
#define BOOSTHTTPCLIENT_H

#include "HttpClient.h"
#include <boost/beast.hpp>
#include <boost/asio.hpp>

namespace http = boost::beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

class BoostHttpClient : public HttpClient {
    protected:
        net::io_context ioc;
        tcp::resolver resolver;
        tcp::socket socket;

    public:
        BoostHttpClient(); // constructor
        std::string makeRequest(const std::string& host, const std::string& target) override; // added parameters
        ~BoostHttpClient() override = default;

    private:
        void connect(const std::string& host); // helper method
};

#endif //BOOSTHTTPCLIENT_H
