#include "UserStore.h"

#include <fstream>

using namespace AudioFingerPrint;

GnString UserStore::LoadSerializedUser(gnsdk_cstr_t clientId)
{
  std::fstream  userRegFile;
  std::string   fileName;
  std::string   serialized;
  GnString    userData;

  fileName = clientId;
  fileName += "_user.txt";

  userRegFile.open(fileName.c_str(), std::ios_base::in);
  if (!userRegFile.fail())
  {
    userRegFile >> serialized;
    userData = serialized.c_str();
  }
  return userData;
}

bool UserStore::StoreSerializedUser(gnsdk_cstr_t clientId, gnsdk_cstr_t userData)
{
  std::fstream userRegFile;
  std::string  fileName;

  fileName = clientId;
  fileName += "_user.txt";

  userRegFile.open(fileName.c_str(), std::ios_base::out);
  if (!userRegFile.fail())
  {
    userRegFile << userData;
    return true;
  }
  return false;
}