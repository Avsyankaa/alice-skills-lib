// Copyright 2018 RomAsya

#ifndef INCLUDES_META_HPP_
#define INCLUDES_META_HPP_

#include <string>

namespace Alice {

class Meta {
 public:
  Meta() = default;
  Meta(std::string locale, std::string timezone, std::string client_id);
  std::string Locale() const { return locale_; }
  std::string Timezone() const { return timezone_; }
  std::string ClientId() const { return client_id_; }

 private:
  std::string locale_;
  std::string timezone_;
  std::string client_id_;
};

}  // namespace Alice

#endif  // INCLUDES_META_HPP_
