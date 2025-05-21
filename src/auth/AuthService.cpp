#include "auth/AuthService.h"
#include "auth/PasswordManager.h"
#include "models/User.h"

#include <iostream>
#include <optional>
#include <sqlite3.h>

std::optional<User> AuthService::login(const std::string& email, const std::string& password) {
    const char* sql = "SELECT id, name, password_hash, role FROM users WHERE email = ?;";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db->getRawDB(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error: " << sqlite3_errmsg(db->getRawDB()) << std::endl;
        return std::nullopt;
    }

    sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string hash = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        std::string role = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));

        if (PasswordManager::verify(password, hash)) {
            return User(id, name, role);
        }
    }

    sqlite3_finalize(stmt);
    return std::nullopt;
}

AuthService::AuthService(std::shared_ptr<Database> db)
    : db(std::move(db)) {} // move pointer into the class

std::optional<User> AuthService::registerUser(const std::string& name, const std::string& email, const std::string& password) {
  try {
    std::string hash = PasswordManager::hash(password);
    int userId = db->addUser(name, email, hash);
    return User(userId, name, "user");
  } catch (const std::exception& e) {
      std::cerr << e.what() << std::endl;
      return std::nullopt;
  }
}
