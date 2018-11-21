// Copyright 2018 RomAsya

#ifndef INCLUDES_BUTTON_HPP_
#define INCLUDES_BUTTON_HPP_

#include <string>

#include <nlohmann/json.hpp>

namespace Alice {
class Button {
 public:
  Button(std::string title, nlohmann::json payload, std::string url, bool hide);
  nlohmann::json ToJson();

 private:
  std::string title_;
  nlohmann::json payload_;
  std::string url_;
  bool hide_;
};
}  // namespace Alice

#endif  // INCLUDES_BUTTON_HPP_
