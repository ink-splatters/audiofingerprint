#pragma once

#include "UserStore.h"

#include "gnsdk.hpp"

#include <memory>

namespace AudioFingerprint
{

using namespace gracenote;
class Processor
{
public:
  Processor(const std::string &settings);
  void process(const std::string &input, const std::string &output);
private:
  std::unique_ptr<GnManager> _manager;
  std::unique_ptr<GnLog> _log;
  std::unique_ptr<UserStore> _userStore;
  std::unique_ptr<GnUser> _user;
  std::unique_ptr<GnLocale> _locale;
};

}