// Copyright 2018 RomAsya
#include <Request.hpp>
#include <Response.hpp>
#include <Skill.hpp>

void my_awesome_callback(const Alice::Request& request,
                         Alice::Response& response) {
  if (request.Command() == "Hello") {
    Alice::Button first_button("Print on button", {}, "http://example.com/",
                               true);
    Alice::Button second_button("Print on button", {}, "http://example.com/",
                                true);
    response.PushButton(first_button);
    response.PushButton(second_button);
    Alice::ButtonPicture button_picture("Print on button",
                                        "http://example.com/", {});
    Alice::Card card("BigImage", "1027858/46r960da47f60207e924",
                     "Title for image", "Description of image", button_picture);
    response.SetCard(card);
    response.SetText("Hi, dear friend!");
    response.SetTts("Hi, dear friend!");
    response.SetEndSession(false);
  }
  return;
}

void buy_elephant_callback(const Alice::Request& request,
                           Alice::Response& response) {
  /*const auto& session = request.Session();
  if (session.IsNew() == true) {
    response.SetText("Hi, buy an elephant!");
    response.SetTts("Hi, buy an elephant!");
    Alice::Button button(
        "Ok", {},
        "https://yandex.ru/images/"
        "search?pos=1&img_url=https%3A%2F%2Fsummerboard.ru%2Fimages%"
        "2Felephants_wallpapers%2F39_elephant.jpg&text=%D1%84%D0%BE%D1%82%D0%"
        "BE%20%D1%81%D0%BB%D0%BE%D0%BD%D0%B0&lr=213&rpt=simage",
        true);
    response.PushButton(button);
    response.SetEndSession(false);
    return;
  }*/
  if (request.RequestType() == Alice::Request::Type::SimpleUtterance) {
    std::string title;
    if (request.Command() == "") {
      title = "Купи слона!";
    } else {
      title =
          "Все говорят " + request.Command() + ", а ты купи слона!";
    }
    response.SetText(title);
    response.SetTts(title);
    Alice::Button button("Я сдаюсь", {"json"}, true);
    response.PushButton(button);
  } else {
    Alice::ButtonPicture button_picture(
        "",
        "http://pngimg.com/uploads/elephants/elephants_PNG18808.png", {"json"});
    Alice::Card card("BigImage", "213044/0bd9aa9bce3a08478953", "", "",
                     button_picture);
    response.SetCard(card);
    response.SetEndSession(true);
  }
}

int main() {
  Skill s;
  s.SetCallback(buy_elephant_callback);
  s.Run();
  return 0;
}
