#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include "models/User.h"
#include <optional>

class SessionManager {
  private:
    std::optional<User> currentUser;

  public:
    void login(const User& user);
    void logout();
    bool isLoggedIn() const;
    std::optional<User> getCurrentUser() const;
};

#endif //SESSIONMANAGER_H
