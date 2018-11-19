// Copyright 2018 RomAsya

#include <Response.hpp>

using nlohmann::json;

namespace Alice {

Response::Response(Request request) {
  SetSession(request.Session());
  SetVersion(request.Version());
	}

void Response::SetText(std::string text) { text_ = std::move(text); }

void Response::SetTts(std::string tts) { tts_ = std::move(tts); }

void Response::SetVersion(std::string version) {
  version_ = std::move(version);
}

void Response::SetEndSession(bool end_session) { end_session_ = end_session; }

void Response::PushButton(Button button) {
  buttons_ref_.push_back(std::move(button));
}

void Response::SetSession(Session session) {
  session_ = Session(session.MessageId() + 1, session.SessionId(),
           session.UserId());
}

void Response::SetCard(Card card) { card_ = std::move(card); }

std::string Response::WithImageToString() {
  nlohmann::json response_small;
  nlohmann::json response;
  response_small["text"] = text_;
  response_small["tts"] = tts_;
  response_small["end_session"] = end_session_;
  response["version"] = version_;
  response_small["card"] = card_.ToJson();
  response["session"] = session_.ToJson();
  nlohmann::json buttons_array;
  for (unsigned i = 0; i < buttons_ref_.size(); ++i) {
    buttons_array.push_back(buttons_ref_[i].ToJson());
  }
  response_small["buttons"] = std::move(buttons_array);
  response["response"] = std::move(response_small);
  return response.dump();
}

std::string Response::WithoutImageToString() {
  nlohmann::json response_small;
  nlohmann::json response;
  response_small["text"] = text_;
  response_small["tts"] = tts_;
  response_small["end_session"] = end_session_;
  response["version"] = version_;
  response["session"] = session_.ToJson();
  nlohmann::json buttons_array;
  for (unsigned i = 0; i < buttons_ref_.size(); ++i) {
    buttons_array.push_back(buttons_ref_[i].ToJson());
  }
  response_small["buttons"] = std::move(buttons_array);
  response["response"] = std::move(response_small);
  return response.dump();
}
}// namespace Alice
