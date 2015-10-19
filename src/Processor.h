#pragma once

#include "UserStore.h"

#include "gnsdk.hpp"

#include <memory>

namespace AudioFingerprint
{

using namespace gracenote;
class Processor: public IGnLogEvents
{
public:
  Processor(const std::string &settings, bool logToScreen);
  void process(const std::string &input, const std::string &output);
public:
  bool LogMessage(gnsdk_uint16_t packageId, GnLogMessageType messageType, gnsdk_uint32_t errorCode, gnsdk_cstr_t message) override;
private:
  std::unique_ptr<GnManager> _manager;
  std::unique_ptr<GnLog> _log;
  std::unique_ptr<UserStore> _userStore;
  std::unique_ptr<GnUser> _user;
  std::unique_ptr<GnLocale> _locale;
};

}