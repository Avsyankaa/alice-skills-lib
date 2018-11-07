// Copyright 2018 RomAsya

#ifndef INCLUDES_CARD_HPP_
#define INCLUDES_CARD_HPP_

#include <string>

#include <nlohmann/json.hpp>

#include "ButtonPicture.hpp"

namespace Alice {

class Card {
public:
  Card() {}
  Card(const std::string &type, const std::string &image_id,
       const std::string &title, const std::string &description,
       const ButtonPicture &button_picture);
  nlohmann::json ToJson();

private:
  std::string type_;
  std::string image_id_;
  std::string title_;
  std::string description_;
  ButtonPicture button_picture_;
};

} // namespace Alice

#endif // INCLUDES_CARD_HPP_
