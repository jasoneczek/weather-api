#include "BoostHttpClient.h"
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <iostream>

namespace http = boost::beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

void BoostHttpClient::makeRequest() {
    try {
        // set up for looking up the server and opening a connection
        net::io_context ioc;
        tcp::resolver resolver(ioc);
        tcp::socket socket(ioc);

        // resolve domain name and connect to server
        auto const results = resolver.resolve("httpbin.org", "80");
        net::connect(socket, results.begin(), results.end());

        // build GET request
        http::request<http::string_body> req(http::verb::get, "/get", 11);
        req.set(http::field::host, "httpbin.org"); // set header

        // send request to server
        http::write(socket, req);

        // store response from server in a readable format
        boost::beast::flat_buffer buffer;
        http::response<http::dynamic_body> res;
        http::read(socket, buffer, res);

        // print response
        std::cout << res << std::endl;

        socket.shutdown(tcp::socket::shutdown_both);

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
