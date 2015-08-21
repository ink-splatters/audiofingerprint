#pragma once

#define GNSDK_STORAGE_SQLITE 1

#include "gnsdk.hpp"

namespace AudioFingerprint
{

using namespace gracenote;

class UserStore : public IGnUserStore
{
public:
  GnString LoadSerializedUser(gnsdk_cstr_t clientId) override;
  bool StoreSerializedUser(gnsdk_cstr_t clientId, gnsdk_cstr_t userData) override;
};

}