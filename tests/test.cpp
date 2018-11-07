// Copyright 2018 RomAsya
#include <gtest/gtest.h>

#include <Meta.hpp>
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

TEST(AliceTest, MetaFromRequest) {
  Alice::Request request(data);
  const auto &meta = request.Meta();
  EXPECT_EQ(meta.Locale(), "ru-RU");
  EXPECT_EQ(meta.Timezone(), "Europe/Moscow");
  EXPECT_EQ(meta.ClientId(), "ru.yandex.searchplugin/5.80");
}

TEST(AliceTest, Meta) {
  Alice::Meta meta{"ru-RU", "Europe/Moscow", "ru.yandex.searchplugin/5.80"};
  EXPECT_EQ(meta.Locale(), "ru-RU");
  EXPECT_EQ(meta.Timezone(), "Europe/Moscow");
  EXPECT_EQ(meta.ClientId(), "ru.yandex.searchplugin/5.80");
}

TEST(AliceTest, SessionFromRequest) {
  Alice::Request request(data);
  const auto &session = request.Session();
  EXPECT_EQ(session.IsNew(), true);
  EXPECT_EQ(session.MessageId(), 4);
  EXPECT_EQ(session.SessionId(), "2eac4854-fce721f3-b845abba-20d60");
  EXPECT_EQ(session.SkillId(), "3ad36498-f5rd-4079-a14b-788652932056");
  EXPECT_EQ(session.UserId(),
            "AC9WC3DF6FCE052E45A4566A48E6B7193774B84814CE49A922E163B8B29881DC");
}

TEST(AliceTest, Session) {
  Alice::Session session{24, "sessionid", "skillid", "userid", false};
  EXPECT_EQ(session.IsNew(), false);
  EXPECT_EQ(session.MessageId(), 24);
  EXPECT_EQ(session.SessionId(), "sessionid");
  EXPECT_EQ(session.SkillId(), "skillid");
  EXPECT_EQ(session.UserId(), "userid");
}

TEST(AliceTest, RequestFromRequest) {
  Alice::Request request(data);
  EXPECT_EQ(request.Version(), "1.0");
  EXPECT_EQ(request.Command(), "hello my friend");
  EXPECT_EQ(request.OriginalUtterance(), "hello my friend");
  EXPECT_EQ(request.RequestType(), Alice::Request::Type::SimpleUtterance);
  EXPECT_EQ(request.IsDangerousContext(), true);
  EXPECT_EQ(request.Payload().dump(), "{}");
}

TEST(AliceTest, ResponseSession) {
  Alice::Session session(
      4, "2eac4854-fce721f3-b845abba-20d60", "",
      "AC9WC3DF6FCE052E45A4566A48E6B7193774B84814CE49A922E163B8B29881DC",
      false);
  std::string result = session.ToJson().dump();
  std::string result1 = "{\"message_id\":4,\"session_id\":\"2eac4854-fce721f3-"
                        "b845abba-20d60\",\"user_id\":"
                        "\"AC9WC3DF6FCE052E45A4566A48E6B7193774B84814CE49A922E1"
                        "63B8B29881DC\"}";
  EXPECT_EQ(result, result1);
}

TEST(AliceTest, ResponseButtonPicture) {
  Alice::ButtonPicture button("Print on button", "http://example.com/", {});
  std::string result = button.ToJson().dump();
  std::string result1 = "{\"payload\":null,\"text\":\"Print on "
                        "button\",\"url\":\"http://example.com/\"}";
  EXPECT_EQ(result, result1);
}

TEST(AliceTest, ResponseCard) {
  Alice::ButtonPicture button("Print on button", "http://example.com/", {});
  Alice::Card card("BigImage", "1027858/46r960da47f60207e924",
                   "Title for image", "Description of image", button);
  std::string result = card.ToJson().dump();
  std::string result1 = "{\"button\":{\"payload\":null,\"text\":\"Print on "
                        "button\",\"url\":\"http://example.com/"
                        "\"},\"description\":\"Description of "
                        "image\",\"image_id\":\"1027858/"
                        "46r960da47f60207e924\",\"title\":\"Title for "
                        "image\",\"type\":\"BigImage\"}";
  EXPECT_EQ(result, result1);
}

TEST(AliceTest, ResponseButton) {
  Alice::Button button("Print on button", {}, "http://example.com/", true);
  std::string result = button.ToJson().dump();
  std::string result1 = "{\"hide\":true,\"payload\":null,\"title\":\"Print on "
                        "button\",\"url\":\"http://example.com/\"}";
  EXPECT_EQ(result, result1);
}

TEST(AliceTest, ResponseButtonArray) {
  Alice::Button button("Print on button", {}, "http://example.com/", true);
  Alice::Response response;
  response.PushButton(button);
  Alice::Session session(
      4, "2eac4854-fce721f3-b845abba-20d60", "",
      "AC9WC3DF6FCE052E45A4566A48E6B7193774B84814CE49A922E163B8B29881DC",
      false);
  Alice::ButtonPicture button_picture("Print on button", "http://example.com/",
                                      {});
  Alice::Card card("BigImage", "1027858/46r960da47f60207e924",
                   "Title for image", "Description of image", button_picture);
  response.SetSession(session);
  response.SetCard(card);
  response.SetText("Hi, dear friend");
  response.SetTts("Hi, dear friend");
  response.SetEndSession(false);
  response.SetVersion("1.0");
  std::string result = response.ToString();
  std::string result1 =
      "{\"response\":{\"buttons\":[{\"hide\":true,\"payload\":null,\"title\":"
      "\"Print on "
      "button\",\"url\":\"http://example.com/"
      "\"}],\"card\":{\"button\":{\"payload\":null,\"text\":\"Print on "
      "button\",\"url\":\"http://example.com/\"},\"description\":\"Description "
      "of "
      "image\",\"image_id\":\"1027858/46r960da47f60207e924\",\"title\":\"Title "
      "for image\",\"type\":\"BigImage\"},\"end_session\":false,\"text\":\"Hi, "
      "dear friend\",\"tts\":\"Hi, dear "
      "friend\"},\"session\":{\"message_id\":4,\"session_id\":\"2eac4854-"
      "fce721f3-b845abba-20d60\",\"user_id\":"
      "\"AC9WC3DF6FCE052E45A4566A48E6B7193774B84814CE49A922E163B8B29881DC\"},"
      "\"version\":\"1.0\"}";
  EXPECT_EQ(result, result1);
}
