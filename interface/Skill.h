#include "Response.h"
namespace Alice {
using CallbackType = std::function<void(Request&, Response&)>;
using HandlerType = std::function<void(Request&, Response&)>;
class Skill {
      Skill ();
      void SetCallback(CallbackType callback);
      bool AddButtonHandler(const std::string& button_title, HandlerType);
      bool run();
};
}