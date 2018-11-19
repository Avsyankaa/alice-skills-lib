
#include <Request.hpp>
#include <Response.hpp>
#include <Skill.hpp>

void my_awesome_callback(const std::string& request, std::string& response) {
  Alice::Request req(request);
  Alice::Response resp(req);
  if (req.Command() == "Hello") {
    Alice::Button button("Print on button", {}, "http://example.com/", true);
    resp.PushButton(button);
    Alice::ButtonPicture button_picture("Print on button",
                                        "http://example.com/", {});
    Alice::Card card("BigImage", "1027858/46r960da47f60207e924",
                     "Title for image", "Description of image", button_picture);
    resp.SetCard(card);
    resp.SetText("Hi, dear friend");
    resp.SetTts("Hi, dear friend");
    resp.SetEndSession(false);
  }
  response = resp.WithImageToString();
  return;
}

int main() {
  Skill s;
  s.setCallback(my_awesome_callback);
  s.run();
  return 0;
}