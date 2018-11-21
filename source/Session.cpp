// Copyright 2018 RomAsya

#include <string>
#include <utility>

#include <boost/optional.hpp>

#include <Session.hpp>

namespace Alice {

Session::Session(size_t message_id,
                 std::string session_id,
                 std::string skill_id,
                 std::string user_id,
                 bool is_new)
    : message_id_(message_id),
      session_id_(std::move(session_id)),
      skill_id_(std::move(skill_id)),
      user_id_(std::move(user_id)),
      is_new_(is_new) {}

Session::Session(size_t message_id, std::string session_id, std::string user_id)
    : message_id_(message_id),
      session_id_(std::move(session_id)),
      user_id_(std::move(user_id)) {}

nlohmann::json Session::ToJson() {
  nlohmann::json session;
  session["message_id"] = message_id_;
  session["session_id"] = session_id_;
  session["user_id"] = user_id_;
  return session;
}

}  // namespace Alice
