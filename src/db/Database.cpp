#include "db/Database.h"
#include <iostream>

// helper function to insert a new user into users table

// ** this method differs from the insertUser function from the class lab #6
// includes error checks and uses SQLITE_TRANSIENT for safety
// throws C++ exceptions if something goes wrong
static void insertUser(sqlite3* db, const std::string& name, const::std::string& email, const std::string& passwordHash, const std::string& role) {
  const char* createSql = "INSERT INTO users (name, email, password_hash, role) VALUES (?, ?, ?, ?)"; // placeholders for the name and email
  sqlite3_stmt* stmt;

  // prepare for execution
  // compile sql string into a statement that the db can run
  if (sqlite3_prepare_v2(db, createSql, -1, &stmt, nullptr) != SQLITE_OK) {
    throw std::runtime_error("Failed to prepare statement");
  }

  // bind name and email string into placeholders
  sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 2, email.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 3, passwordHash.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 4, role.c_str(), -1, SQLITE_TRANSIENT);

  // run the statement
  if (sqlite3_step(stmt) != SQLITE_DONE) {
    sqlite3_finalize(stmt); // finalize even if it fails
    throw std::runtime_error("Failed to execute statement");
  }

  // free the memory
  sqlite3_finalize(stmt);
}

// constructor - opens or creates the db
Database::Database(const std::string& dbPath) {
  if (sqlite3_open(dbPath.c_str(), &db)) {
    throw std::runtime_error("Could not open database");
  }
  initDB();
}

// destructor
Database::~Database() {
  if (db) {
    sqlite3_close(db);
    std::cout << "Closed database successfully." << std::endl;
  }
}

// create tables if db doesn't exist
void Database::initDB() {
  const char* createSql = R"sql(
    CREATE TABLE IF NOT EXISTS users (
      id INTEGER PRIMARY KEY AUTOINCREMENT,
      name TEXT NOT NULL,
      email TEXT UNIQUE NOT NULL,
      password_hash TEXT NOT NULL,
      role TEXT NOT NULL DEFAULT 'user'
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

// call insert user helper function
void Database::addUser(const std::string& name, const std::string& email, const std::string& passwordHash, const std::string& role) {
  insertUser(db, name, email, passwordHash, role);
}