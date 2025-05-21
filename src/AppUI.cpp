#include "AppUI.h"
#include <iostream>
#include <iomanip> // for std::setw
#include <db/Database.h>
#include <auth/AuthService.h>
#include <auth/SessionManager.h>

void AppUI::run() {
    std::shared_ptr<Database> db;
    // std::optional<User> currentUser;
    SessionManager session;

    try {
        // create or connect to db
        db = std::make_shared<Database>("weather.sqlite");

        // gives authservice access to db
        AuthService auth(db);

        std::string choice;
        std::cout << "[1] Register\n";
        std::cout << "[2] Login\n";
        std::cout << "[0] Exit program\n";
        std::getline(std::cin, choice);

        if (choice == "0") {
            std::cout << "Goodbye!\n";
            return;
        }

        std::string name, email, password;

        // register
        if (choice == "1") {
            std::cout << "Enter your name: ";
            std::getline(std::cin, name);
            std::cout << "Enter your email: ";
            std::getline(std::cin, email);
            std::cout << "Enter your password: ";
            std::getline(std::cin, password);

            // try to register using authservice
            if (auth.registerUser(name, email, password)) {
                std::cout << "Successfully registered!\n";

                // create a temp user object for the session
                session.login(User(-1, name, "user"));
            } else {
                std::cout << "Failed to register!\n";
                return;
            }
        }

        // login
        else if (choice == "2") {
            while (true) {
                std::cout << "Enter your email: ";
                std::getline(std::cin, email);
                std::cout << "Enter your password: ";
                std::getline(std::cin, password);

                // try to login with authservice
                auto user = auth.login(email, password);
                if (user) {
                    session.login(*user);
                    std::cout << "Login successful!\n";
                    break;
                } else {
                    std::cout << "Incorrect email or password. Try again or type 0 to exit.\n";
                    std::string cancel;
                    std::getline(std::cin, cancel);
                    if (cancel == "0") return;
                }
            }
        }

        else {
            std::cout << "Invalid input!\n";
            return;
        }


        // *** old test code

      // test inserting a user through AuthService
      // auth.registerUser("hashtestuser", "hashtestuser@example.com", "hashtest123");
      //
      // auto user = auth.login("hashtestuser@example.com", "hashtest123");
      //
      // if (user) {
      //     std::cout << "Login successful" << std::endl;
      // } else {
      //     std::cout << "Login failed" << std::endl;
      // }

    } catch (const std::exception& e) {
      std::cerr << e.what() << std::endl;
      return;
    }

    // === WELCOME ====
    if (session.isLoggedIn()) {
        std::cout << "\nHello, " << session.getCurrentUser()->username << "\n";
        std::cout << std::setw(14) << std::left << "\n========== WELCOME TO THE WEATHER REPORT ==========\n";
    }


    // === WEATHER QUERY LOOP ===
    WeatherClient client;
    std::string city;

    while (true) {
        std::cout << "\nEnter:\n[1] Get weather\n[2] Logout\n[0] Exit program\n> ";
        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "0") {
            std::cout << "Goodbye!\n";
            break;
        }

        if (choice == "2") {
            std::cout << "Logging out...\n";
            session.logout();
            return run(); // restart login or register
        }

        if (choice == "1") {
            std::cout << "Enter city name: ";
            std::getline(std::cin, city);

            if (city.empty()) {
                std::cout << "Please enter a city name.\n";
                continue;
            }

            try {
                auto [weather, airQuality] = client.getWeather(city);
                printReport(weather, airQuality);
                db->saveQuery(session.getCurrentUser()->id, city);
            } catch (const std::exception& e) {
                std::cout << "\nError: " << e.what() << "\n";
            }
        } else {
            std::cout << "Invalid input!\n";
        }
    }
}

// display report
void AppUI::printReport(const WeatherData& weather, const AirQualityData& airQuality) {
    std::cout << "\n========== Current Weather for " << weather.location << ", " << weather.country << " ==========\n";
    std::cout << "\n";
    std::cout << std::setw(14) << std::left << "Temperature" << " | " << weather.tempC << "°C / " << weather.tempF << "°F\n";
    std::cout << std::setw(14) << std::left << "Condition" << " | " << weather.condition << "\n";
    std::cout << std::setw(14) << std::left << "Wind" << " | " << weather.windKph << "kph / " << weather.windMph << "mph\n";
    std::cout << std::setw(14) << std::left << "Humidity" << " | " << weather.humidity << "%\n";

    if (airQuality.epaIndex != -1) {
        std::cout << std::setw(14) << std::left << "Air Quality" << " | " << airQuality.epaCategory << "\n";
    } else {
        std::cout << "\nAir quality data not available.\n";
    }
}


