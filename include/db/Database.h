#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <models/Query.h>
#include <string>
#include <vector>



class Database {
  public:
    explicit Database(const std::string& dbPath); // constructor
    ~Database();

    sqlite3* getRawDB() const; // to safely expose raw pointer

    // added parameters
    int addUser(const std::string& name, const std::string& email, const std::string& passwordHash, const std::string& role = "user");

    void saveQuery(int userId, const std::string& city);

    std::vector<Query> getRecentQueries(int userId);

  private:
    sqlite3 *db; // pointer to database connection

    void initDB(); // create tables
};

#endif //DATABASE_H
