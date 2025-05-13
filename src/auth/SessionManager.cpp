#include "auth/SessionManager.h"

void SessionManager::login(const User& user) {
  currentUser = user;
}

void SessionManager::logout() {
  currentUser.reset();
}

bool SessionManager::isLoggedIn() const {
  return currentUser.has_value();
}

std::optional<User> SessionManager::getCurrentUser() const {
  return currentUser;
}
