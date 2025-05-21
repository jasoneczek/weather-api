#include "db/Database.h"
#include <iostream>

// helper function to insert a new user into users table
// static - only Database.cpp has access
static void insertUser(sqlite3* db, const std::string& name, const::std::string& email, const std::string& passwordHash, const std::string& role) {
  // sqlite expects c style string
  const char* createSql = "INSERT INTO users (name, email, password_hash, role) VALUES (?, ?, ?, ?)"; // placeholders for the name and email
  sqlite3_stmt* stmt;

  // prepare for execution
  // compile sql string into a statement that the db can run
  if (sqlite3_prepare_v2(db, createSql, -1, &stmt, nullptr) != SQLITE_OK) {
    throw std::runtime_error("Failed to prepare statement");
  }

  // bind values from the sql statement (fill in ?'s..)
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
    // std::cout << "Closed database successfully." << std::endl;
  }
}

// create tables if db doesn't exist
void Database::initDB() {
  const char* createUserTableSql = R"sql(
    CREATE TABLE IF NOT EXISTS users (
      id INTEGER PRIMARY KEY AUTOINCREMENT,
      name TEXT NOT NULL,
      email TEXT UNIQUE NOT NULL,
      password_hash TEXT NOT NULL,
      role TEXT NOT NULL DEFAULT 'user'
    );
  )sql";

  const char* createQueryTableSql = R"sql(
    CREATE TABLE IF NOT EXISTS queries (
      id INTEGER PRIMARY KEY AUTOINCREMENT,
      user_id INTEGER NOT NULL,
      city TEXT NOT NULL,
      timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
      FOREIGN KEY(user_id) REFERENCES users(id)
    );
  )sql";

  char* errMsg = nullptr;

  // create users table
  if (sqlite3_exec(db, createUserTableSql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
    std::cerr << "Error creating users table: " << errMsg << std::endl;
    sqlite3_free(errMsg);
    throw std::runtime_error("Could not create users table");
  }

  // create queries table
  if (sqlite3_exec(db, createQueryTableSql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
    std::cerr << "Error creating query table: " << errMsg << std::endl;
    sqlite3_free(errMsg);
    throw std::runtime_error("Could not create query table");
  }
}

// call insert user helper function
void Database::addUser(const std::string& name, const std::string& email, const std::string& passwordHash, const std::string& role) {
  insertUser(db, name, email, passwordHash, role);
}

// expose raw sqlite3* for AuthService
sqlite3* Database::getRawDB() const {
  return db;
}

// save weather queries
void Database::saveQuery(int userId, const std::string& city) {
  const char* insertSql = "INSERT INTO queries (user_id, city) VALUES (?, ?)";
  sqlite3_stmt* stmt;

  if (sqlite3_prepare_v2(db, insertSql, -1, &stmt, nullptr) != SQLITE_OK) {
    throw std::runtime_error("Failed to prepare statement");
  }

  sqlite3_bind_int(stmt, 1, userId);
  sqlite3_bind_text(stmt, 2, city.c_str(), -1, SQLITE_TRANSIENT);

  if (sqlite3_step(stmt) != SQLITE_DONE) {
    sqlite3_finalize(stmt);
    throw std::runtime_error("Failed to execute statement");
  }

  sqlite3_finalize(stmt);
}