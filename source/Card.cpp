// Copyright 2018 RomAsya

#include <Card.hpp>

namespace Alice {

Card::Card(const std::string &type, const std::string &image_id,
           const std::string &title, const std::string &description,
           const ButtonPicture &button_picture)
    : type_(std::move(type)), image_id_(std::move(image_id)),
      title_(std::move(title)), description_(std::move(description)),
      button_picture_(button_picture) {}

nlohmann::json Card::ToJson() {
  nlohmann::json card;
  nlohmann::json button_picture = button_picture_.ToJson();
  card["type"] = type_;
  card["image_id"] = image_id_;
  card["title"] = title_;
  card["description"] = description_;
  card["button"] = button_picture;
  return card;
}

} // namespace Alice
