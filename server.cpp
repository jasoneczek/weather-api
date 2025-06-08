#include "include/api/AppComponent.h"

#include "include/api/WeatherController.h"
#include "include/api/AuthController.h"

#include "db/Database.h"
#include "auth/AuthService.h"
#include "auth/SessionManager.h"

#include "oatpp/network/Server.hpp"

#include <iostream>

void runServer() {
    oatpp::Environment::init();

    AppComponent components; // Create scope Environment components

    // get components from AppComponent
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, contentMappers);
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);

    // add weather controller
    router->addController(std::make_shared<WeatherController>(contentMappers));

    // set up auto service and session manager
    auto database = std::make_shared<Database>("weather.sqlite");
    auto authService = std::make_shared<AuthService>(database);
    auto sessionManager = std::make_shared<SessionManager>();

    // add auth controller
    auto authController = std::make_shared<AuthController>(contentMappers, authService, sessionManager);
    router->addController(authController);

    /* create server */
    oatpp::network::Server server(connectionProvider, connectionHandler);

    OATPP_LOGd("Server", "Running on port 8000...", connectionProvider->getProperty("port").toString()->c_str());

    server.run();

    std::cout << "\nEnvironment:\n";
    std::cout << "objectsCount = " << oatpp::Environment::getObjectsCount() << "\n";
    std::cout << "objectsCreated = " << oatpp::Environment::getObjectsCreated() << "\n\n";

    oatpp::Environment::destroy();
}

