cmake_minimum_required(VERSION 3.30)
project(weather_app)

set(CMAKE_CXX_STANDARD 20)

# BOOST FOR HTTP
find_package(Boost 1.87.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# SQLITE
find_package(SQLite3 REQUIRED)
include_directories(${SQLite3_INCLUDE_DIRS})

# OATPP
find_package(oatpp REQUIRED)
include_directories(/usr/local/include)

# include_directories(${oatpp_INCLUDE_DIRS})
# include_directories(/usr/local/include)



# PATHS
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
        src/AppUI.cpp
        src/db/Database.cpp
        src/auth/AuthService.cpp
        src/auth/PasswordManager.cpp
        src/auth/SessionManager.cpp

        server.cpp
)

# LINK LIBRARIES
target_link_libraries(weather_app
        PRIVATE
        SQLite::SQLite3
        oatpp::oatpp
        # oatpp::oatpp-json
        # oatpp::oatpp-test
)