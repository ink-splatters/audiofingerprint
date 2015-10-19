#include "StatusEventsHandler.h"
#include "SimpleLogger.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <fstream>

namespace AudioFingerprint
{

using boost::property_tree::ptree;

namespace
{

ptree GetTrack(const std::string &artist, const std::string & album, const GnTrack & track )
{
  SimpleLogger::instance() << "\t\tMatched track:" << std::endl;
  SimpleLogger::instance() << "\t\t\tnumber: " << track.TrackNumber() << std::endl;
  SimpleLogger::instance() << "\t\t\ttitle: " << track.Title().Display() << std::endl;
  SimpleLogger::instance() << "\t\t\tartist: " << artist << std::endl;
  SimpleLogger::instance() << "\t\t\ttrack length (ms): " << track.Duration() << std::endl;

  ptree ptTrack;
  ptTrack.put<std::string>("artist", artist);
  ptTrack.put<std::string>("album", album);
  ptTrack.put<std::string>("title", track.Title().Display());
  ptTrack.put<uint32_t>("length_ms", track.Duration());

  return ptTrack;
}

void OutputResult(const std::string &outputFile, const GnResponseAlbums& albums)
{
  SimpleLogger::instance()<<"\tAlbum count: " << albums.Albums().count() << std::endl;
    
  int matchCounter = 0;
  ptree result, tracks;
    
  for (auto it = albums.Albums().begin(); it != albums.Albums().end(); ++it)
  {
    SimpleLogger::instance() << "\tMatch " << ++matchCounter << " - Album Title:\t" << it->Title().Display() << std::endl;
    auto track = GetTrack(it->Artist().Name().Display(), it->Title().Display(), it->TrackMatched());
    tracks.push_back(std::make_pair(std::string(), track));
  }

  result.add_child("tracks", tracks);

  auto & out = outputFile.empty() ? std::cout : std::ofstream(outputFile);
  boost::property_tree::write_json(out, result);
}

}

StatusEventHandler::StatusEventHandler(const std::string &outputFile):
  _outputFile(outputFile)
{

}

void StatusEventHandler::StatusEvent(GnStatus status, gnsdk_uint32_t percent_complete, gnsdk_size_t bytes_total_sent, gnsdk_size_t bytes_total_received, IGnCancellable& canceller)
{    
  GNSDK_UNUSED(canceller);

  switch (status)
  {
    case gnsdk_status_unknown:
        SimpleLogger::instance() <<"Unknown ";
        break;
        
    case gnsdk_status_connecting:
        SimpleLogger::instance() <<"Busy... " << std::endl;
        break;

    case gnsdk_status_disconnected:
        SimpleLogger::instance() <<"Disconnected" << std::endl;
        break;
        
    case gnsdk_status_complete:
        SimpleLogger::instance() <<"Done" << std::endl;
        break;
        
    default:
        break;
  }
}

void StatusEventHandler::MusicIdStreamProcessingStatusEvent(GnMusicIdStreamProcessingStatus status, IGnCancellable& canceller)
{
  GNSDK_UNUSED(status);
  GNSDK_UNUSED(canceller);
}

void StatusEventHandler::StatusEventHandler::MusicIdStreamIdentifyingStatusEvent(GnMusicIdStreamIdentifyingStatus status, IGnCancellable& canceller)
{
  if (status == kStatusIdentifyingEnded)
  {
    SimpleLogger::instance() <<  "Identification complete" << std::endl;
    canceller.SetCancel(true);
  }
}

void StatusEventHandler::MusicIdStreamAlbumResult(GnResponseAlbums& album_result, IGnCancellable& canceller)
{
  OutputResult(_outputFile, album_result);
}

void StatusEventHandler::MusicIdStreamIdentifyCompletedWithError(GnError& e)
{
  std::cerr << e.ErrorAPI() << "\t" << std::hex << e.ErrorCode() << "\t" <<  e.ErrorDescription() << std::endl;
}

}