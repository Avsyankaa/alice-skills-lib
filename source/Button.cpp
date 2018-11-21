// Copyright 2018 RomAsya

#include <Button.hpp>

namespace Alice {

Button::Button(std::string title,
               nlohmann::json payload,
               std::string url,
               bool hide)
    : title_(std::move(title)),
      payload_(payload),
      url_(std::move(url)),
      hide_(hide) {}

nlohmann::json Button::ToJson() {
  nlohmann::json button;
  button["title"] = title_;
  button["payload"] = payload_;
  button["url"] = url_;
  button["hide"] = hide_;
  return button;
}

}  // namespace Alice
