#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <iostream>

namespace http = boost::beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

int main() {
    try {
        net::io_context ioc;
        tcp::resolver resolver(ioc); // turns domain into IP addresses
        tcp::socket socket(ioc); // connect to server

        auto const results = resolver.resolve("httpbin.org", "80"); // look up IP addresses for httpbin.org on port 80
        net::connect(socket, results.begin(), results.end()); // connect socket to first available IP address

        http::request<http::string_body> req(http::verb::get, "/get", 11); // create GET request
        req.set(http::field::host, "httpbin.org"); // set header

        http::write(socket, req); // send http request over the network

        boost::beast::flat_buffer buffer; // temporary storage buffer that catches raw bytes from server
        http::response<http::dynamic_body> res; // prepares an http response object
        http::read(socket, buffer, res); // parses data into readable version into res

        std::cout << res << std::endl; // print response

        socket.shutdown(tcp::socket::shutdown_both); // shut down the socket

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}