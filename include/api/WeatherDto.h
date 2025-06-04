#ifndef WEATHERDTO_H
#define WEATHERDTO_H

#include "oatpp/data/mapping/type/Object.hpp"
#include "oatpp/macro/codegen.hpp"
#include "oatpp/Types.hpp"

#include OATPP_CODEGEN_END(DTO)

class WeatherDto : public oatpp::DTO {
  DTO_INIT(WeatherDto, DTO);
  DTO_FIELD(String, report);
};

#include OATPP_CODEGEN_END(DTO)

#endif //WEATHERDTO_H
