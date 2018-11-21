// Copyright 2018 RomAsya

#include <string>
#include <utility>

#include <Meta.hpp>

namespace Alice {

Meta::Meta(std::string locale, std::string timezone, std::string client_id)
    : locale_(std::move(locale)),
      timezone_(std::move(timezone)),
      client_id_(std::move(client_id)) {}

}  // namespace Alice
