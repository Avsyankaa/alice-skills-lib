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
  Card(std::string type,
       std::string image_id,
       std::string title,
       std::string description,
       ButtonPicture button_picture);
  nlohmann::json ToJson();

 private:
  std::string type_;
  std::string image_id_;
  std::string title_;
  std::string description_;
  ButtonPicture button_picture_;
};

}  // namespace Alice

#endif  // INCLUDES_CARD_HPP_
