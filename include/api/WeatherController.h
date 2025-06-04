#ifndef WEATHERCONTROLLER_H
#define WEATHERCONTROLLER_H

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/web/server/HttpRouter.hpp"
#include "oatpp/web/mime/ContentMappers.hpp"

#include "oatpp/network/tcp/server/ConnectionProvider.hpp"

#include "oatpp/json/ObjectMapper.hpp"

#include "oatpp/macro/component.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

class WeatherController : public oatpp::web::server::api::ApiController {
  public:
    WeatherController(OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, contentMappers))
  		: oatpp::web::server::api::ApiController(contentMappers) {}



    ENDPOINT("GET", "/weather", getWeather,
			 QUERY(String, city)) {
      if (!city) {
        return createResponse(Status::CODE_400, "City not found");
      }

      // temporary response
      oatpp::String message = "Weather for " + city;
      return createResponse(Status::CODE_200, message);
    }
};

#include OATPP_CODEGEN_END(ApiController)

#endif //WEATHERCONTROLLER_H
