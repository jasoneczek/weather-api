#include "include/api/AppComponent.h"

#include "include/api/WeatherController.h"

#include "oatpp/network/Server.hpp"

#include <iostream>

void runServer() {
    oatpp::Environment::init();

    AppComponent components; // Create scope Environment components

    /* Get router component */
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);

    // oatpp::web::server::api::Endpoints docEndpoints;

    // docEndpoints.append(router->addController(WeatherController::createShared())->getEndpoints());

    // router->addController(oatpp::swagger::Controller::createShared(docEndpoints));
    router->addController(std::make_shared<WeatherController>());

    /* Get connection handler component */
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);

    /* Get connection provider component */
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);

    /* create server */
    oatpp::network::Server server(connectionProvider, connectionHandler);

    OATPP_LOGd("Server", "Running on port 8000...", connectionProvider->getProperty("port").toString()->c_str());

    server.run();

    std::cout << "\nEnvironment:\n";
    std::cout << "objectsCount = " << oatpp::Environment::getObjectsCount() << "\n";
    std::cout << "objectsCreated = " << oatpp::Environment::getObjectsCreated() << "\n\n";

    oatpp::Environment::destroy();
}

