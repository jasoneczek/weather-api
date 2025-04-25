#include "BoostHttpClient.h"
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <iostream>

namespace http = boost::beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

// initialize the resolver and socket objects in the constructor
BoostHttpClient::BoostHttpClient() : resolver(ioc), socket(ioc) {}

// connection method
void BoostHttpClient::connect(const std::string& host) {
    auto const results = resolver.resolve(host, "80");
    net::connect(socket, results.begin(), results.end());
}

// make request method
void BoostHttpClient::makeRequest(const std::string& host, const std::string& target) {
    try {
        connect(host);

        // build GET request
        http::request<http::string_body> req(http::verb::get, target, 11);
        req.set(http::field::host, host); // set header

        // send request to server
        http::write(socket, req);

        // store response from server in a readable format
        boost::beast::flat_buffer buffer;
        http::response<http::dynamic_body> res;
        http::read(socket, buffer, res);

        // Had to switch from 'std::cout << res' to this because WeatherAPI's response
        // wasn't printing correctly — 'res' works with httpbin.org but for WeatherAPI,
        // manually extracting the body content using buffers_to_string
        std::cout << boost::beast::buffers_to_string(res.body().data()) << std::endl;

        socket.shutdown(tcp::socket::shutdown_both);

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
