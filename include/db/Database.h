#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>

class Database {
  public:
    Database(const std::string& dbPath); // constructor
    ~Database();

  private:
    sqlite3 *db; // pointer to database connection

    void initDB(); // create tables
};

#endif //DATABASE_H
