#ifndef AUTHSERVICES_H
#define AUTHSERVICES_H

#include <string>
#include <memory> // for std::shared_ptr
#include "db/Database.h"

class AuthService {
  private:
    std::shared_ptr<Database> db;

  public:
    // constructor gives access to db when creating an AuthService
    AuthService(std::shared_ptr<Database> db);

    // added a new parameter for the raw password
    bool registerUser(const std::string& name, const std::string& email, const std::string& password, const std::string& role = "user");
};

#endif //AUTHSERVICES_H
