#include "Request.h"
#include "Button.h"
#include "ButtonPicture.h"
#include "Card.h"
namespace Alice {
class Response {
public:
    const Session& Session() const;
    void SetVersion(std::string& Version) const;
    const Card& Card() const; // картиночки
    std::vector <Button> ButtonsRef(); // кнопочки
    std::string ToString() const; // вместо ToJson()

    void SetText(std::string&) const; //  текст, который показываем пользователю
    void SetTts(std::string&) const; // текст, который показываем пользователю, в формате TTS
    void End_session(bool&) const; // признак конца разговора
};
}