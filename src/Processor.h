#pragma once

#undef GNSDK_TASTE
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
};

}