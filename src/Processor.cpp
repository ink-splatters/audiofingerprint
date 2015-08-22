#include "Processor.h"
#include "AudioSource.h"
#include "StatusEventsHandler.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <fstream>

namespace
{
const std::string APP_VERSION="1.0";
}

namespace AudioFingerprint
{

Processor::Processor(const std::string& settings)
{
  using boost::property_tree::ptree;
  using namespace gracenote::storage_sqlite;


  ptree pt ;
  std::ifstream file(settings);
  
  boost::property_tree::read_json(file, pt);

  const auto & clientID = pt.get<std::string>("ClientID");
  const auto & clientTag = pt.get<std::string>("ClientTag");
  const auto & licenseFile = pt.get<std::string>("LicenseFile");

  _manager = std::unique_ptr<GnManager>(new GnManager(licenseFile.c_str(), kLicenseInputModeFilename));

  std::cout << std::endl << "GNSDK Product Version : " << _manager->ProductVersion() << " \t(built " << _manager->BuildDate() << ")" << std::endl;

  std::cout << "Initializing..." << std::endl;

  _log = std::unique_ptr<GnLog>(new GnLog(
    "AudioFingerPrint.log",
    GnLogFilters().Error().Warning(),
    GnLogColumns().All(),
    GnLogOptions().MaxSize(0).Archive(false),
    GNSDK_NULL
    )
  );
  
  _log->Enable(kLogPackageAllGNSDK);

  GnStorageSqlite::Enable();

  _userStore = std::unique_ptr<UserStore>(new UserStore());
  _user = std::unique_ptr<GnUser>(new GnUser(*(_userStore.get()), clientID.c_str(), clientTag.c_str(), APP_VERSION.c_str()));
  _user->Options().LookupMode(kLookupModeOnline);

  _locale = std::unique_ptr<GnLocale>(new GnLocale ( kLocaleGroupMusic, kLanguageEnglish, kRegionDefault, kDescriptorSimplified, *(_user.get())));
  _locale->SetGroupDefault();


  std::cout << "Done." << std::endl;
}

void Processor::process(const std::string &input, const std::string &output)
{
  StatusEventHandler eventsHandler(output);
  AudioSource         audioSource(input);
  GnMusicIdStream     stream(*(_user.get()), kPresetRadio, &eventsHandler);

  // stream.Options().ResultSingle(true);
  stream.AudioProcessStart(audioSource);
  stream.IdentifyAlbum();
}

}