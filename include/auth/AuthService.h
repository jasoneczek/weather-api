#ifndef AUTHSERVICES_H
#define AUTHSERVICES_H

#include "db/Database.h"
#include "models/User.h"

#include <string>
#include <memory> // for std::shared_ptr
#include <optional> // for std::optional


class AuthService {
  private:
    std::shared_ptr<Database> db;

  public:
    // changed to explicit to avoid implicit conversions
    explicit AuthService(std::shared_ptr<Database> db);

    // added a new parameter for the raw password
    bool registerUser(const std::string& name, const std::string& email, const std::string& password);

    std::optional<User> login(const std::string& email, const std::string& password);
};

#endif //AUTHSERVICES_H
