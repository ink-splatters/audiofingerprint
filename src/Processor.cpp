#include "Processor.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>


#include <fstream>

namespace AudioFingerprint
{

Processor::Processor(const std::string& settings)
{
  using boost::property_tree::ptree;

  ptree pt ;
  std::ifstream file(settings);
  
  boost::property_tree::read_json(file, pt);

  const auto & clientID = pt.get<std::string>("ClientID");
  const auto & clientTag = pt.get<std::string>("ClientTag");
  const auto & licenseFile = pt.get<std::string>("LicenseFile");

  _manager = std::unique_ptr<GnManager>(new GnManager(licenseFile.c_str(), kLicenseInputModeFilename));
}

}