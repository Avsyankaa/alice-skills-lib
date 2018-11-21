// Copyright 2018 RomAsya

#include <ButtonPicture.hpp>

namespace Alice {
ButtonPicture::ButtonPicture(std::string text,
                             std::string url,
                             nlohmann::json payload)
    : text_(std::move(text)), url_(std::move(url)), payload_(payload) {}

nlohmann::json ButtonPicture::ToJson() {
  nlohmann::json button_picture;
  button_picture["text"] = text_;
  button_picture["url"] = url_;
  button_picture["payload"] = payload_;
  return button_picture;
}

}  // namespace Alice
