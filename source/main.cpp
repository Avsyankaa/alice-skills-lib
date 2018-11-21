
#include <Request.hpp>
#include <Response.hpp>
#include <Skill.hpp>

void my_awesome_callback(const Alice::Request& request,
                         Alice::Response& response) {
  if (request.Command() == "Hello") {
    Alice::Button first_button("Print on button", {}, "http://example.com/", true);
    Alice::Button second_button("Print on button", {}, "http://example.com/", true);
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

int main() {
  Skill s;
  s.SetCallback(my_awesome_callback);
  s.Run();
  return 0;
}