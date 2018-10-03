#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <iostream>
#include <boost/optional.hpp>
#include "Meta.h"
#include "Session.h"
namespace Alice {
enum RequestType {SimpleUtterance, ButtonPressed};
class Request {
public:
    Request(const std::string&); // конструктор, который парсит Json от пользователя и инициализирует поля класса

    const Meta& Meta() const;
    const Session& Session() const;
    const std::srting& Version() const;

    std::string Command() const;
    std::string OriginalUtterance() const;
    RequestType Type() const;
    bool IsDangerousContext() const;
    std::string Payload() const;

};
}