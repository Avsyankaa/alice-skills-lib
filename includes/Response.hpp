// Copyright 2018 RomAsya

#ifndef INCLUDES_RESPONSE_HPP_
#define INCLUDES_RESPONSE_HPP_

#include <iostream>
#include <string>
#include <vector>

#include <boost/optional.hpp>
#include <nlohmann/json.hpp>

#include "Button.hpp"
#include "ButtonPicture.hpp"
#include "Card.hpp"
#include "Request.hpp"
#include "Session.hpp"

namespace Alice {

class Response {
 public:
  explicit Response(const Request& request);
  void SetCard(Card card);
  void PushButton(Button button);
  std::string ToString();
  void SetText(std::string text);
  void SetTts(std::string tts);
  void SetEndSession(bool end_session);

 private:
  void SetVersion(std::string version);
  void SetSession(const Session& session);
  std::string version_;
  Session session_;
  bool end_session_;
  std::string text_;
  std::string tts_;
  std::vector<Button> buttons_ref_;
  Card card_;
  bool is_image_on_ = false;
};

}  // namespace Alice

#endif  // INCLUDES_RESPONSE_HPP_
