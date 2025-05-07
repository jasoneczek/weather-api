#include "db/Database.h"
#include <iostream>

Database::Database(const std::string& dbPath) {
  if (sqlite3_open(dbPath.c_str(), &db)) {
    throw std::runtime_error("Could not open database");
  }
  initDB();
}

Database::~Database() {
  if (db) {
    sqlite3_close(db);
    std::cout << "Closed database successfully." << std::endl;
  }
}

void Database::initDB() {
  const char* createSql = R"sql(
    CREATE TABLE IF NOT EXISTS users (
      id INTEGER PRIMARY KEY AUTOINCREMENT,
      name TEXT NOT NULL,
      email TEXT UNIQUE NOT NULL
    );
  )sql";

  char* errMsg = nullptr;
  int rc = sqlite3_exec(db, createSql, nullptr, nullptr, &errMsg);
  if (rc != SQLITE_OK) {
    std::cerr << "Error creating database: " << errMsg << std::endl;
    sqlite3_free(errMsg);
    throw std::runtime_error("Could not create database");
  } else {
    std::cout << "Database created successfully." << std::endl;
  }
}