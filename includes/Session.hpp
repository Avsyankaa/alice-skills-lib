// Copyright 2018 RomAsya

#ifndef INCLUDES_SESSION_HPP_
#define INCLUDES_SESSION_HPP_

#include <string>

#include <boost/optional.hpp>
#include <nlohmann/json.hpp>

namespace Alice {

class Session {
 public:
  Session() = default;
  Session(size_t message_id,
          std::string session_id,
          std::string skill_id,
          std::string user_id,
          bool is_new);
  Session(size_t message_id, std::string session_id, std::string user_id);
  nlohmann::json ToJson();
  bool IsNew() const { return is_new_; }
  size_t MessageId() const { return message_id_; }
  std::string SessionId() const { return session_id_; }
  std::string SkillId() const { return skill_id_; }
  std::string UserId() const { return user_id_; }

 private:
  size_t message_id_;
  std::string session_id_;
  std::string skill_id_;
  std::string user_id_;
  bool is_new_ = false;
};

}  // namespace Alice

#endif  // INCLUDES_SESSION_HPP_
