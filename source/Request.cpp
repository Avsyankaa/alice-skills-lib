// Copyright 2018 RomAsya

#include <Request.hpp>

using nlohmann::json;

namespace Alice {

Request::Request(const std::string& input_data) {
  auto request_obj = json::parse(input_data);

  if (request_obj.find("meta") == request_obj.end() ||
      request_obj.find("request") == request_obj.end() ||
      request_obj.find("session") == request_obj.end() ||
      request_obj.find("version") == request_obj.end()) {
    return;
  }

  meta_ = Alice::Meta(request_obj["meta"]["locale"],
                      request_obj["meta"]["timezone"],
                      request_obj["meta"]["client_id"]);

  session_ = Alice::Session(
      request_obj["session"]["message_id"],
      request_obj["session"]["session_id"], request_obj["session"]["skill_id"],
      request_obj["session"]["user_id"], request_obj["session"]["new"]);

  command_ = request_obj["request"]["command"];
  original_utterance_ = request_obj["request"]["original_utterance"];
  if (request_obj["request"]["type"] == "SimpleUtterance")
    type_ = Type::SimpleUtterance;
  else
    type_ = Type::ButtonPressed;

  version_ = request_obj["version"];

  const json& request = request_obj["request"];
  payload_ = request["payload"];
  if (request.find("markup") != request.end())
    is_dangerous_context_ = true;
}

}  // namespace Alice
