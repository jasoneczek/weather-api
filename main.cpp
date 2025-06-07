#include "AppUI.h"
#include <iostream>
#include <string>

extern void runServer();

int main() {
    std::string mode;
    std::cout << "Enter mode:\n [1] CLI\n [2] Server\n> ";
    std::cin >> mode;

    if (mode == "1") {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        AppUI app;
        app.run();
    } else if (mode == "2") {
        runServer();
    } else {
        std::cout << "Invalid mode.\n";
    }

    return 0;
}