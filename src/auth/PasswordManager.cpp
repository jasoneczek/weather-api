#include "auth/PasswordManager.h"

// for now i'm just testing with a prefix
std::string PasswordManager::hash(const std::string& password) {
  return "hashed_" + password;
}

bool PasswordManager::verify(const std::string& password, const std::string& hash) {
  return hash == PasswordManager::hash(password);
}
