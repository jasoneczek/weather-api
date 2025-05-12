#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>



class Database {
  public:
    explicit Database(const std::string& dbPath); // constructor
    ~Database();

    sqlite3* getRawDB() const; // to safely expose raw pointer

    // added parameters
    void addUser(const std::string& name, const std::string& email, const std::string& passwordHash, const std::string& role = "user");

  private:
    sqlite3 *db; // pointer to database connection

    void initDB(); // create tables
};

#endif //DATABASE_H
