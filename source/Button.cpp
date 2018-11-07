// Copyright 2018 RomAsya

#include <Button.hpp>

namespace Alice {

Button::Button(const std::string &title, const nlohmann::json &payload,
               const std::string &url, const bool hide)
    : title_(std::move(title)), payload_(payload), url_(std::move(url)),
      hide_(hide) {}

nlohmann::json Button::ToJson() {
  nlohmann::json button;
  button["title"] = title_;
  button["payload"] = payload_;
  button["url"] = url_;
  button["hide"] = hide_;
  return button;
}

} // namespace Alice
