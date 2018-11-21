// Copyright 2018 RomAsya

#ifndef INCLUDES_REQUEST_HPP_
#define INCLUDES_REQUEST_HPP_

#include <iostream>
#include <string>
#include <vector>

#include <boost/optional.hpp>
#include <nlohmann/json.hpp>

#include "Meta.hpp"
#include "Session.hpp"

namespace Alice {

class Request {
 public:
  enum class Type { SimpleUtterance, ButtonPressed };
  explicit Request(const std::string& input_data);
  const Alice::Meta& Meta() const { return meta_; }
  const Alice::Session& Session() const { return session_; }
  std::string Version() const { return version_; }
  std::string Command() const { return command_; }
  std::string OriginalUtterance() const { return original_utterance_; }
  Alice::Request::Type RequestType() const { return type_; }
  bool IsDangerousContext() const { return is_dangerous_context_; }
  nlohmann::json Payload() const { return payload_; }

 private:
  Alice::Meta meta_;
  Alice::Session session_;
  std::string command_;
  std::string original_utterance_;
  nlohmann::json payload_;
  std::string version_;
  Alice::Request::Type type_;
  bool is_dangerous_context_ = false;
};

}  // namespace Alice

#endif  // INCLUDES_REQUEST_HPP_
