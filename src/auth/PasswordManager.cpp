#include "auth/PasswordManager.h"
#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>

std::string PasswordManager::hash(const std::string& password) {
  boost::uuids::detail::md5 hash;
  boost::uuids::detail::md5::digest_type digest;
  hash.process_bytes(password.data(), password.size());
  hash.get_digest(digest);

  const auto* charDigest = reinterpret_cast<const char*>(&digest);
  std::string result;
  boost::algorithm::hex(charDigest, charDigest + sizeof(digest), std::back_inserter(result));
  return result;
  // REMOVED (used for testing) -- return "hashed_" + password;
}

bool PasswordManager::verify(const std::string& raw, const std::string& hashed) {
  return hash(raw) == hashed;
}
