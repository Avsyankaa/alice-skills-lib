#include<string>
#include<WString.h>
#include<vector>
#include<nlohmann/json.hpp>
#include<iostream>
namespace Alice {
class Request {
public:
    Request(const Json&); // конструктор, который парсит Json от пользователя и инициализирует поля класса

    const Meta& Meta() const;
    const Session& Session() const;
    const std::srting& Version() const;

    std::wstring Command() const;
    std::wstring OriginalUtterance() const;
    RequestType Type() const;
    bool IsDangerousContext() const;
    Json Payload() const;

};

class Meta {
public:
    Meta(std::string Locale, std::string Timezone, std::string ClientId); //конструктор класса Meta
    std::string Locale() const;
    std::string Timezone() const;
    std::string ClientId() const;
};

class Session {
public:
    Session (bool InNew, size_t MessageId, std::string SessionId, std::string SkillId, std::string UserId); // Конструктор класса Session для Requets
    Session (size_t MessageId, std::string SessionId, std::string UserId); // Конструктор класса Session для Response
    bool InNew() const;
    size_t MessageId() const;
    std::string SessionId() const;
    std::string SkillId() const;
    std::string UserId() const;
};


class Response {
public:
    const Session& Session() const;
    const std::srting& Version(std::string Version) const;
    const Card& Card() const; // картиночки
    std::vector <Button> Buttons(); // кнопочки
    void ToJson(const Json&);

    std::wstring Text(std::wstring&) const; //  текст, который показываем пользователю
    std::wstring Tts(std::wstring&) const; // текст, который показываем пользователю, в формате TTS
    bool End_session(bool&) const; // признак конца разговора

    void ToJson (Json&); //создаем json- ответ
};

class Button {
    std::wstring Title(std::wstring&) const; // Текст кнопки
    Json Payload(Json&) const; // Произвольный JSON, который Яндекс.Диалоги должны отправить обработчику, если данная кнопка будет нажата.
    std::string Url(std::string&) const; // URL, который должна открывать кнопка, максимум 1024 байта.
    bool Hide(bool&) const; // Признак того, что кнопку нужно убрать после следующей реплики пользователя.
};

class Card {
    std::string Type(std::string&) const; // Тип карточки.
    std::string Image_id(std::string&) const; // Идентификатор изображения.
    std::wstring Title(std::wstring&) const; // Заголовок для изображения.
    std::wstring Description(std::wstring&) const; // Описание изображения.
    const Button_Picture & Button_Picture() const; // Что будет, если нажать на изображение
};

class Button_Picture { // Класс для кнопочки, расположенной на картиночке
    std::string Text(std::string&) const; // Текст, который будет отправлен навыку по нажатию на изображение в качестве команды пользователя.
    std::string Url(std::string&) const; // URL, который должно открывать нажатие по изображению.
    Json Payload(Json&) const; //Произвольный JSON, который Яндекс.Диалоги должны отправить обработчику, если пользователь нажмет на изображение.
};

 class Skill {
      Skill (); // ???? Какие параметры- response и request?
      bool SetCallback( void (*f)(Request&, Response&));
      bool AddButtonHandler(); //????
      bool run();// ?????
    };
}  // namespace Alice
