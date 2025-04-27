cmake_minimum_required(VERSION 3.30)
project(weather_app)

set(CMAKE_CXX_STANDARD 20)

# BOOST FOR HTTP
find_package(Boost 1.87.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

include_directories(include)
include_directories(/opt/homebrew/include)

add_executable(weather_app
        main.cpp
        src/BoostHttpClient.cpp
        src/WeatherClient.cpp
        src/Config.cpp
        src/JsonParser.cpp
        src/WeatherData.cpp
        src/AirQualityData.cpp
)
