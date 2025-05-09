#include "auth/AuthService.h"
#include "auth/PasswordManager.h"

#include <iostream>

AuthService::AuthService(std::shared_ptr<Database> db)
    : db(std::move(db)) {} // move pointer into the class

bool AuthService::registerUser(const std::string& name, const std::string& email, const std::string& password, const std::string& role) {
  try {
    std::string hash = PasswordManager::hash(password);
    db->addUser(name, email, hash, role);
    return true;
  } catch (const std::exception& e) {
      std::cerr << e.what() << std::endl;
      return false;
  }
}
