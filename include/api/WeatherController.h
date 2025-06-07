#ifndef WEATHERCONTROLLER_H
#define WEATHERCONTROLLER_H

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/web/server/HttpRouter.hpp"
#include "oatpp/web/mime/ContentMappers.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "oatpp/json/ObjectMapper.hpp"
#include "oatpp/macro/component.hpp"

#include "WeatherClient.h"
#include <nlohmann/json.hpp>
#include <string>

#include OATPP_CODEGEN_BEGIN(ApiController)

class WeatherController : public oatpp::web::server::api::ApiController {
  public:
    WeatherController(OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, contentMappers))
  		: oatpp::web::server::api::ApiController(contentMappers) {}

    ENDPOINT("GET", "/weather", getWeather,
			 QUERY(String, city)) {
      if (!city || city->empty()) {
        return createResponse(Status::CODE_400, "City not found");
      }

      try {
          WeatherClient client;
          std::string cityStr = city;

          auto [weather, air] = client.getWeather(cityStr);

          nlohmann::json result = {
              { "location", weather.location },
              { "country", weather.country },
              { "tempC", weather.tempC },
              { "tempF", weather.tempF },
              { "condition", weather.condition },
              { "windKph", weather.windKph },
              { "windMph", weather.windMph },
              { "humidity", weather.humidity },
              { "epaIndex", air.epaIndex },
              { "epaCategory", air.epaCategory }
          };

          return createResponse(Status::CODE_200, result.dump(2));

      } catch (const std::exception& e) {
            return createResponse(Status::CODE_500, e.what());
      }

      // temporary response
      // oatpp::String message = "Weather for " + city;
      // return createResponse(Status::CODE_200, message);
    }
};

#include OATPP_CODEGEN_END(ApiController)

#endif //WEATHERCONTROLLER_H
