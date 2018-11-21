// Copyright 2018 RomAsya

#ifndef INCLUDES_BUTTONPICTURE_HPP_
#define INCLUDES_BUTTONPICTURE_HPP_

#include <string>

#include <boost/optional.hpp>
#include <nlohmann/json.hpp>

namespace Alice {
class ButtonPicture {  // Класс для кнопочки, расположенной на картиночке
 public:
  ButtonPicture() = default;
  ButtonPicture(std::string text, std::string url, nlohmann::json payload);
  nlohmann::json ToJson();

 private:
  std::string text_;
  std::string url_;
  nlohmann::json payload_;
};
}  // namespace Alice

#endif  // INCLUDES_BUTTONPICTURE_HPP_
