#include "Processor.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <fstream>

using namespace AudioFingerPrint;

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

  std::cout << std::endl << "GNSDK Product Version : " << _manager->ProductVersion() << " \t(built " << _manager->BuildDate() << ")" << std::endl;

  _log = std::unique_ptr<GnLog>(new GnLog(
    "AudioFingerPrint.log",
    GnLogFilters().Error().Warning(),
    GnLogColumns().All(),
    GnLogOptions().MaxSize(0).Archive(false),
    GNSDK_NULL
    )
  );
  
  _log->Enable(kLogPackageAllGNSDK);      /* Enable for all GNSDK packages */ 

  GnStorageSqlite::Enable();

  _userStore = std::unique_ptr<UserStore>(new UserStore());
  _user = std::unique_ptr<GnUser>(new GnUser(userStore, clientId, clientIdTag, applicationVersion));
  _user->Options().LookupMode(kLookupModeOnline);

  _locale = std::unique_ptr<GnLocale>(new GnLocale ( kLocaleGroupMusic, kLanguageEnglish, kRegionDefault, kDescriptorSimplified, *(_user.get())));
  _locale->SetGroupDefault();
}

void Processor::process(const std::string &input, const std::string &output)
{

}