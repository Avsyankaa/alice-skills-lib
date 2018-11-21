// Copyright 2018 RomAsya

#include <gtest/gtest.h>

#include <Request.hpp>
#include <Response.hpp>

const char data[] = R"({
      "meta": {
        "locale": "ru-RU",
        "timezone": "Europe/Moscow",
        "client_id": "ru.yandex.searchplugin/5.80"
      },
      "request": {
        "command": "hello my friend",
        "original_utterance": "hello my friend",
        "type": "SimpleUtterance",
        "markup": {
          "dangerous_context": true
        },
        "payload": {}
      },
      "session": {
        "new": true,
        "message_id": 4,
        "session_id": "2eac4854-fce721f3-b845abba-20d60",
        "skill_id": "3ad36498-f5rd-4079-a14b-788652932056",
        "user_id": "AC9WC3DF6FCE052E45A4566A48E6B7193774B84814CE49A922E163B8B29881DC"
      },
      "version": "1.0"
    })";

TEST(AliceTest, ResponseSession) {
  Alice::Session session(
      4, "2eac4854-fce721f3-b845abba-20d60", "",
      "AC9WC3DF6FCE052E45A4566A48E6B7193774B84814CE49A922E163B8B29881DC",
      false);
  EXPECT_EQ(
      session.ToJson().dump(),
      R"({"message_id":4,)"
      R"("session_id":"2eac4854-fce721f3-b845abba-20d60","user_id":")"
      R"(AC9WC3DF6FCE052E45A4566A48E6B7193774B84814CE49A922E163B8B29881DC)"
      R"("})");
}

TEST(AliceTest, ResponseButtonPicture) {
  Alice::ButtonPicture button("Print on button", "http://example.com/", {});
  EXPECT_EQ(button.ToJson().dump(),
            R"({"payload":null,"text":"Print on )"
            R"(button","url":"http://example.com/"})");
}

TEST(AliceTest, ResponseCard) {
  Alice::ButtonPicture button("Print on button", "http://example.com/", {});
  Alice::Card card("BigImage", "1027858/46r960da47f60207e924",
                   "Title for image", "Description of image", button);
  EXPECT_EQ(
      card.ToJson().dump(),
      R"({"button":{"payload":null,"text":"Print on )"
      R"(button","url":"http://example.com/)"
      R"("},"description":"Description of )"
      R"(image","image_id":"1027858/46r960da47f60207e924","title":"Title )"
      R"(for image","type":"BigImage"})");
}

TEST(AliceTest, ResponseButton) {
  Alice::Button button("Print on button", {}, "http://example.com/", true);
  EXPECT_EQ(button.ToJson().dump(),
            R"({"hide":true,"payload":null,"title":"Print on )"
            R"(button","url":"http://example.com/"})");
}

TEST(AliceTest, ResponseButtonArray) {
  Alice::Button button("Print on button", {}, "http://example.com/", true);
  Alice::Request request(data);
  Alice::Response response(request);
  response.PushButton(button);
  Alice::ButtonPicture button_picture("Print on button", "http://example.com/",
                                      {});
  Alice::Card card("BigImage", "1027858/46r960da47f60207e924",
                   "Title for image", "Description of image", button_picture);
  response.SetCard(card);
  response.SetText("Hi, dear friend");
  response.SetTts("Hi, dear friend");
  response.SetEndSession(false);
  EXPECT_EQ(
      response.ToString(),
      R"({"response":{"buttons":[{"hide":true,"payload":null,"title":")"
      R"(Print on )"
      R"(button","url":"http://example.com/)"
      R"("}],"card":{"button":{"payload":null,"text":"Print on )"
      R"(button","url":"http://example.com/)"
      R"("},"description":"Description of )"
      R"(image","image_id":"1027858/46r960da47f60207e924","title":"Title )"
      R"(for image","type":"BigImage"},"end_session":false,"text":"Hi, )"
      R"(dear friend","tts":"Hi, dear )"
      R"(friend"},"session":{"message_id":5,"session_id":"2eac4854-)"
      R"(fce721f3-b845abba-20d60","user_id":")"
      R"(AC9WC3DF6FCE052E45A4566A48E6B7193774B84814CE49A922E163B8B29881D)"
      R"(C"},"version":"1.0"})");
}
