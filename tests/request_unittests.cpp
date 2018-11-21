// Copyright 2018 RomAsya

#include <gtest/gtest.h>

#include <Request.hpp>

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
  const auto& meta = request.Meta();
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
  const auto& session = request.Session();
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
