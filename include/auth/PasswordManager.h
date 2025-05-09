#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H

#include <string>

class PasswordManager {
  public:
    // hash password before storing in db
    static std::string hash(const std::string& password);

    // check if entered password mashes hashed
    static bool verify(const std::string& password, const std::string& hash);
};

#endif //PASSWORDMANAGER_H
