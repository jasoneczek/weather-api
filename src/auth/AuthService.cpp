#include "auth/AuthService.h"
#include <iostream>

AuthService::AuthService(std::shared_ptr<Database> db)
    : db(std::move(db)) {} // move pointer into the class

bool AuthService::registerUser(const std::string& name, const std::string& email) {
  try {
    db->addUser(name, email);
    return true;
  } catch (const std::exception& e) {
      std::cerr << e.what() << std::endl;
      return false;
  }
}
