#ifndef AUTHCONTROLLER_H
#define AUTHCONTROLLER_H

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/web/mime/ContentMappers.hpp"
#include "oatpp/json/ObjectMapper.hpp"
#include "oatpp/macro/component.hpp"

#include "auth/AuthService.h"
#include "auth/SessionManager.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include OATPP_CODEGEN_BEGIN(ApiController)

class AuthController : public oatpp::web::server::api::ApiController {
  private:
    std::shared_ptr<AuthService> authService;
    std::shared_ptr<SessionManager> sessionManager;

  public:
    AuthController(std::shared_ptr<oatpp::web::mime::ContentMappers> contentMappers,
                  std::shared_ptr<AuthService> authService,
                  std::shared_ptr<SessionManager> sessionManager)
    : oatpp::web::server::api::ApiController(contentMappers),
          authService(authService),
          sessionManager(sessionManager) {}

  ENDPOINT("POST", "/register", registerUser,
          BODY_STRING(String, body)) {
    try {
      json parsed = json::parse(body->c_str());

      std::string name = parsed.value("name", "");
      std::string email = parsed.value("email", "");
      std::string password = parsed.value("password", "");

      if (name.empty() || email.empty() || password.empty()) {
        return createResponse(Status::CODE_400, "Invalid email/password");
      }

      auto userOpt = authService->registerUser(name, email, password);
      if (userOpt) {
        sessionManager->login(*userOpt);
        return createResponse(Status::CODE_200, "User registered successfully");
      }

      return createResponse(Status::CODE_400, "Invalid email/password");

    } catch (const std::exception &e) {
      return createResponse(Status::CODE_400, e.what());
    }
  }
};



#include OATPP_CODEGEN_END(ApiController)

#endif // AUTHCONTROLLER_H

