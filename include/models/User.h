#ifndef USER_H
#define USER_H

#include <string>

// user class currently based on lecture 7 lab materials

class User {
  public:
    int id;
    std::string username;
    std::string role;

    User(int id, const std::string& username, const std::string& role)
    : id(id), username(username), role(role) {}

    bool isAdmin() const { return role == "admin"; }
};

#endif //USER_H
