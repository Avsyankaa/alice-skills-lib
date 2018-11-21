// Copyright 2018 RomAsya

#include <Card.hpp>

namespace Alice {

Card::Card(std::string type,
           std::string image_id,
           std::string title,
           std::string description,
           ButtonPicture button_picture)
    : type_(std::move(type)),
      image_id_(std::move(image_id)),
      title_(std::move(title)),
      description_(std::move(description)),
      button_picture_(std::move(button_picture)) {}

nlohmann::json Card::ToJson() {
  nlohmann::json card;
  card["type"] = type_;
  card["image_id"] = image_id_;
  card["title"] = title_;
  card["description"] = description_;
  card["button"] = button_picture_.ToJson();
  return card;
}

}  // namespace Alice
