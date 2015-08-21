#include "StatusEventsHandler.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <fstream>

namespace AudioFingerprint
{

namespace
{

void DisplayTrack(const std::string &artist, GnTrack track )
{
    std::cout << "\t\tMatched track:" << std::endl;
    std::cout << "\t\t\tnumber: " << track.TrackNumber() << std::endl;
    std::cout << "\t\t\ttitle: " << track.Title().Display() << std::endl;
    std::cout << "\t\t\tartist: " << artist << std::endl;
    std::cout << "\t\t\ttrack length (ms): " << track.Duration() << std::endl;
}

void OutputResult(const std::string &outputFile, const GnResponseAlbums& albums)
{
  using boost::property_tree::ptree;

  std::cout<<"\tAlbum count: " << response.Albums().count() << std::endl;
    
  int matchCounter = 0;
  metadata::album_iterator it_album     = response.Albums().begin();

  ptree result, tracks;
    
  for (; it_album != response.Albums().end(); ++it_album)
  {
    std::cout << "\tMatch " << ++matchCounter << " - Album Title:\t" <<  << std::endl;
        display_track(it_album->Artist().Name().Display(), it_album->TrackMatched());

    ptree track;
    track.add_child("artist", it_album->Artist().Name().Display());
    track.add_child("album", it_album->Title().Display());
    track.add_child("title", it_album->TrackMatched().Title().Display());
    track.add_child("length_ms", it_album->TrackMatched().Duration());

    tracks.push_back(std::make_pair(std::string(), track))

  }

  result.add_child("tracks", tracks);

  std::ofstream file(outputFile);  
  boost::property_tree::write_json(file, result);
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
              std::cout <<"Unknown ";
              break;
              
          case gnsdk_status_connecting:
              std::cout <<"Connecting... " << percent_complete << "%%" << std::endl;;
              break;
              
          case gnsdk_status_sending:
              std::cout <<"Sending... " << percent_complete << "%%" << std::endl;;
              break;
              
          case gnsdk_status_receiving:
              std::cout <<"Receiving... " << percent_complete << "%%" << std::endl;;
              break;
              
          case gnsdk_status_disconnected:
              std::cout <<"Disconnected" << std::endl;
              break;
              
          case gnsdk_status_complete:
              std::cout <<"Complete" << std::endl;
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
        std::cout << std::endl << "Identification complete" << std::endl;
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