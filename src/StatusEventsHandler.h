#pragma once

#include "gnsdk.hpp"

#include <string>

namespace AudioFingerprint
{

class StatusEventHandler : public IGnMusicIdStreamEvents
{
  std::string _outputFile;
public:
  StatusEventHandler(const std::string &outputFile);
  
  void StatusEvent(GnStatus status, gnsdk_uint32_t percent_complete, gnsdk_size_t bytes_total_sent, gnsdk_size_t bytes_total_received, IGnCancellable& canceller) override;
  void MusicIdStreamProcessingStatusEvent(GnMusicIdStreamProcessingStatus status, IGnCancellable& canceller) override;
  void MusicIdStreamIdentifyingStatusEvent(GnMusicIdStreamIdentifyingStatus status, IGnCancellable& canceller) override;
  void MusicIdStreamAlbumResult(GnResponseAlbums& album_result, IGnCancellable& canceller) override;
  void MusicIdStreamIdentifyCompletedWithError(GnError& e) override;
};

}