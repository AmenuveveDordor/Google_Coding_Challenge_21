//
//  main.cpp
//  coding_challenge
//
//  Created by Amenuveve Dordor on 01/07/2021.
//

#include "commandparser.h"
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

CommandParser::CommandParser(VideoPlayer&& vp) : mVideoPlayer(std::move(vp)) {}

void CommandParser::executeCommand(const std::vector<std::string>& command) {
  if (command.empty()) {
    std::cout << "No commands passed in to executeCommand, that is unexpected"
              << std::endl;
    return;
  }

  if (command[0] == "NUMBER_OF_VIDEOS") {
    mVideoPlayer.numberOfVideos();
  } else if (command[0] == "SHOW_ALL_VIDEOS") {
    mVideoPlayer.showAllVideos();
  } else if (command[0] == "PLAY") {
    if (command.size() != 2) {
      std::cout << "Please enter PLAY command followed by video_id."
                << std::endl;
    } else {
      mVideoPlayer.playVideo(command[1]);
    }
  } else if (command[0] == "PLAY_RANDOM") {
    mVideoPlayer.playRandomVideo();
  } else if (command[0] == "STOP") {
    mVideoPlayer.stopVideo();
  } else if (command[0] == "PAUSE") {
    mVideoPlayer.pauseVideo();
  } else if (command[0] == "CONTINUE") {
    mVideoPlayer.continueVideo();
  } else if (command[0] == "SHOW_PLAYING") {
    mVideoPlayer.showPlaying();
  } else if (command[0] == "CREATE_PLAYLIST") {
    if (command.size() != 2) {
      std::cout << "Please enter CREATE_PLAYLIST command followed by video_id."
                << std::endl;
    } else {
      mVideoPlayer.createPlaylist(command[1]);
    }
  } else if (command[0] == "ADD_TO_PLAYLIST") {
    if (command.size() != 3) {
      std::cout << "Please enter ADD_TO_PLAYLIST command followed by playlist "
                   "name and video_id."
                << std::endl;
    } else {
      mVideoPlayer.addVideoToPlaylist(command[1], command[2]);
    }
  } else if (command[0] == "REMOVE_FROM_PLAYLIST") {
    if (command.size() != 3) {
      std::cout << "Please enter REMOVE_FROM_PLAYLIST command followed by "
                   "playlist name and video_id."
                << std::endl;
    } else {
      mVideoPlayer.removeFromPlaylist(command[1], command[2]);
    }
  } else if (command[0] == "CLEAR_PLAYLIST") {
    if (command.size() != 2) {
      std::cout
          << "Please enter CLEAR_PLAYLIST command followed by a playlist name."
          << std::endl;
    } else {
      mVideoPlayer.clearPlaylist(command[1]);
    }
  } else if (command[0] == "DELETE_PLAYLIST") {
    if (command.size() != 2) {
      std::cout
          << "Please enter DELETE_PLAYLIST command followed by a playlist name."
          << std::endl;
    } else {
      mVideoPlayer.deletePlaylist(command[1]);
    }
  } else if (command[0] == "SHOW_PLAYLIST") {
    if (command.size() != 2) {
      std::cout
          << "Please enter SHOW_PLAYLIST command followed by a playlist name."
          << std::endl;
    } else {
      mVideoPlayer.showPlaylist(command[1]);
    }
  } else if (command[0] == "SHOW_ALL_PLAYLISTS") {
    mVideoPlayer.showAllPlaylists();
  } else if (command[0] == "SEARCH_VIDEOS") {
    if (command.size() != 2) {
      std::cout
          << "Please enter SEARCH_VIDEOS command followed by a search term."
          << std::endl;
    } else {
      mVideoPlayer.searchVideos(command[1]);
    }
  } else if (command[0] == "SEARCH_VIDEOS_WITH_TAG") {
    if (command.size() != 2) {
      std::cout << "Please enter SEARCH_VIDEOS_WITH_TAG command followed by a "
                   "video tag."
                << std::endl;
    } else {
      mVideoPlayer.searchVideosWithTag(command[1]);
    }
  } else if (command[0] == "FLAG_VIDEO") {
    switch (command.size()) {
      case 2:
        mVideoPlayer.flagVideo(command[1]);
        break;
      case 3:
        mVideoPlayer.flagVideo(command[1], command[2]);
        break;
      default:
        std::cout << "Please enter FLAG_VIDEO command followed by a video_id "
                     "and an optional flag reason."
                  << std::endl;
    }
  } else if (command[0] == "ALLOW_VIDEO") {
    if (command.size() != 2) {
      std::cout << "Please enter ALLOW_VIDEO command followed by a video_id."
                << std::endl;
    } else {
      mVideoPlayer.allowVideo(command[1]);
    }
  } else if (command[0] == "HELP") {
    getHelp();
  } else {
    std::cout << "Please enter a valid command, type HELP for a list of "
                 "available commands."
              << std::endl;
  }
}

void CommandParser::getHelp() const {
  static const char* const helpText = R"(
Available commands:
    NUMBER_OF_VIDEOS - Shows how many videos are in the library.
    SHOW_ALL_VIDEOS - Lists all videos from the library.
    PLAY <video_id> - Plays specified video.
    PLAY_RANDOM - Plays a random video from the library.
    STOP - Stop the current video.
    PAUSE - Pause the current video.
    CONTINUE - Resume the current paused video.
    SHOW_PLAYING - Displays the title, url and paused status of the video that is currently playing (or paused).
    CREATE_PLAYLIST <playlist_name> - Creates a new (empty) playlist with the provided name.
    ADD_TO_PLAYLIST <playlist_name> <video_id> - Adds the requested video to the playlist.
    REMOVE_FROM_PLAYLIST <playlist_name> <video_id> - Removes the specified video from the specified playlist
    CLEAR_PLAYLIST <playlist_name> - Removes all the videos from the playlist.
    DELETE_PLAYLIST <playlist_name> - Deletes the playlist.
    SHOW_PLAYLIST <playlist_name> - List all the videos in this playlist.
    SHOW_ALL_PLAYLISTS - Display all the available playlists.
    SEARCH_VIDEOS <search_term> - Display all the videos whose titles contain the search_term.
    SEARCH_VIDEOS_WITH_TAG <tag_name> -Display all videos whose tags contains the provided tag.
    FLAG_VIDEO <video_id> <flag_reason> - Mark a video as flagged.
    ALLOW_VIDEO <video_id> - Removes a flag from a video.
    HELP - Displays help.
    EXIT - Terminates the program execution.
)";
  std::cout << helpText << std::endl;
}
#pragma once

#include <string>
#include <vector>
#include "videoplayer.h"
class CommandParser {
 private:
  VideoPlayer mVideoPlayer;

  void getHelp() const;

 public:
  CommandParser(VideoPlayer&& vp);

  CommandParser(const CommandParser&) = delete;
  CommandParser& operator=(const CommandParser&) = delete;

  CommandParser(CommandParser&&) = default;
  CommandParser& operator=(CommandParser&&) = default;

  // Executes the given user command.
  void executeCommand(const std::vector<std::string>& command);
};

#include "helper.h"

#include <iostream>
#include <sstream>
#include <vector>

std::string trim(std::string toTrim) {
  size_t trimPos = toTrim.find_first_not_of(" \t");
  toTrim.erase(0, trimPos);
  trimPos = toTrim.find_last_not_of(" \t");
  if (std::string::npos != trimPos) {
    toTrim.erase(trimPos + 1);
  }
  return toTrim;
}

std::vector<std::string> splitlines(std::string output) {
  std::vector<std::string> commandOutput;
  std::stringstream ss(output);
  std::string line;
  while (std::getline(ss, line, '\n')) {
    commandOutput.emplace_back(line);
  }
  return commandOutput;
}
#pragma once

#include <string>
#include <vector>

std::string trim(std::string s);

std::vector<std::string> splitlines(std::string output);
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <vector>

#include "commandparser.h"
#include "helper.h"
#include "videolibrary.h"
#include "videoplayer.h"

int main() {
  std::cout << "Hello and welcome to YouTube, what would you like to do? "
               "Enter HELP for list of available commands or EXIT to terminate."
            << std::endl;

  std::string userInput;
  std::string command;
  std::vector<std::string> commandList;
  VideoPlayer vp;
  CommandParser cp = CommandParser(std::move(vp));

  for (;;) {
    std::cout << "YT> ";
    if (!std::getline(std::cin, userInput)) {
      break;
    }
    if (userInput.empty()) {
      std::cout << "Please enter a valid command, type HELP for a list of "
                   "available commands."
                << std::endl;
    } else {
      std::stringstream test(userInput);
      while (std::getline(test, command, ' ')) {
        command = trim(command);
        commandList.push_back(command);
      }
      std::transform(commandList[0].begin(), commandList[0].end(),
                     commandList[0].begin(),
                     [](char c) { return static_cast<char>(std::toupper(c)); });
      if (commandList[0] == "EXIT") {
        break;
      }
      cp.executeCommand(commandList);
      commandList.clear();
    }
  }
  std::cout
      << "YouTube has now terminated it's execution. Thank you and goodbye!"
      << std::endl;
}
#include "video.h"

#include <iostream>
#include <utility>
#include <vector>

Video::Video(std::string&& title, std::string&& videoId,
             std::vector<std::string>&& tags) :
  mTitle(std::move(title)),
  mVideoId(std::move(videoId)),
  mTags(std::move(tags)) {
}

const std::string& Video::getTitle() const { return mTitle; }

const std::string& Video::getVideoId() const { return mVideoId; }

const std::vector<std::string>& Video::getTags() const { return mTags; }
#pragma once

#include <string>
#include <vector>

/**
 * A class used to represent a video.
 */
class Video {
 private:
  std::string mTitle;
  std::string mVideoId;
  std::vector<std::string> mTags;

 public:
  Video(std::string&& title, std::string&& videoId,
        std::vector<std::string>&& tags);

  // Returns the title of the video.
  const std::string& getTitle() const;

  // Returns the video id of the video.
  const std::string& getVideoId() const;

  // Returns a readonly collection of the tags of the video.
  const std::vector<std::string>& getTags() const;
};

#include "videolibrary.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <vector>

#include "helper.h"
#include "video.h"

VideoLibrary::VideoLibrary() {
  std::ifstream file("./src/videos.txt");
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      std::stringstream linestream(line);
      std::string title;
      std::string id;
      std::string tag;
      std::vector<std::string> tags;
      std::getline(linestream, title, '|');
      std::getline(linestream, id, '|');
      while (std::getline(linestream, tag, ',')) {
        tags.emplace_back(trim(std::move(tag)));
      }
      Video video = Video(trim(std::move(title)), trim(id), std::move(tags));
      mVideos.emplace(trim(std::move(id)), std::move(video));
    }
  } else {
    std::cout << "Couldn't find videos.txt" << std::endl;
  }
}

std::vector<Video> VideoLibrary::getVideos() const {
  std::vector<Video> result;
  for (const auto& video : mVideos) {
    result.emplace_back(video.second);
  }
  return result;
}

const Video* VideoLibrary::getVideo(const std::string& videoId) const {
  const auto found = mVideos.find(videoId);
  if (found == mVideos.end()) {
    std::cout << "Video not found in video library" << std::endl;
    return nullptr;
  } else {
    return &(found->second);
  }
}

#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "video.h"
class VideoLibrary {
 private:
  std::unordered_map<std::string, Video> mVideos;

 public:
  VideoLibrary();

  // This class is not copyable to avoid expensive copies.
  VideoLibrary(const VideoLibrary&) = delete;
  VideoLibrary& operator=(const VideoLibrary&) = delete;

  // This class is movable.
  VideoLibrary(VideoLibrary&&) = default;
  VideoLibrary& operator=(VideoLibrary&&) = default;

  std::vector<Video> getVideos() const;
  const Video *getVideo(const std::string& videoId) const;
};

#include "videoplayer.h"
#include <iostream>

void VideoPlayer::numberOfVideos() {
  std::cout << mVideoLibrary.getVideos().size() << " videos in the library"
            << std::endl;
}

void VideoPlayer::showAllVideos() {
  std::cout << "showAllVideos needs implementation" << std::endl;
}

void VideoPlayer::playVideo(const std::string& videoId) {
  std::cout << "playVideo needs implementation" << std::endl;
}

void VideoPlayer::stopVideo() {
  std::cout << "stopVideo needs implementation" << std::endl;
}

void VideoPlayer::playRandomVideo() {
  std::cout << "playRandomVideo needs implementation" << std::endl;
}

void VideoPlayer::pauseVideo() {
  std::cout << "pauseVideo needs implementation" << std::endl;
}

void VideoPlayer::continueVideo() {
  std::cout << "continueVideo needs implementation" << std::endl;
}

void VideoPlayer::showPlaying() {
  std::cout << "showPlaying needs implementation" << std::endl;
}

void VideoPlayer::createPlaylist(const std::string& playlistName) {
  std::cout << "createPlaylist needs implementation" << std::endl;
}

void VideoPlayer::addVideoToPlaylist(const std::string& playlistName,
                                     const std::string& videoId) {
  std::cout << "addVideoToPlaylist needs implementation" << std::endl;
}

void VideoPlayer::showAllPlaylists() {
  std::cout << "showAllPlaylists needs implementation" << std::endl;
}

void VideoPlayer::showPlaylist(const std::string& playlistName) {
  std::cout << "showPlaylist needs implementation" << std::endl;
}

void VideoPlayer::removeFromPlaylist(const std::string& playlistName,
                                     const std::string& videoId) {
  std::cout << "removeFromPlaylist needs implementation" << std::endl;
}

void VideoPlayer::clearPlaylist(const std::string& playlistName) {
  std::cout << "clearPlaylist needs implementation" << std::endl;
}

void VideoPlayer::deletePlaylist(const std::string& playlistName) {
  std::cout << "deletePlaylist needs implementation" << std::endl;
}

void VideoPlayer::searchVideos(const std::string& searchTerm) {
  std::cout << "searchVideos needs implementation" << std::endl;
}

void VideoPlayer::searchVideosWithTag(const std::string& videoTag) {
  std::cout << "searchVideosWithTag needs implementation" << std::endl;
}

void VideoPlayer::flagVideo(const std::string& videoId) {
  std::cout << "flagVideo needs implementation" << std::endl;
}

void VideoPlayer::flagVideo(const std::string& videoId, const std::string& reason) {
  std::cout << "flagVideo needs implementation" << std::endl;
}

void VideoPlayer::allowVideo(const std::string& videoId) {
  std::cout << "allowVideo needs implementation" << std::endl;
}

#pragma once
#include <string>
#include "videolibrary.h"
class VideoPlayer {
 private:
  VideoLibrary mVideoLibrary;

 public:
  VideoPlayer() = default;

  // This class is not copyable to avoid expensive copies.
  VideoPlayer(const VideoPlayer&) = delete;
  VideoPlayer& operator=(const VideoPlayer&) = delete;

  // This class is movable.
  VideoPlayer(VideoPlayer&&) = default;
  VideoPlayer& operator=(VideoPlayer&&) = default;

  void numberOfVideos();
  void showAllVideos();
  void playVideo(const std::string& videoId);
  void stopVideo();
  void playRandomVideo();
  void pauseVideo();
  void continueVideo();
  void showPlaying();
  void createPlaylist(const std::string& playlistName);
  void addVideoToPlaylist(const std::string& playlistName, const std::string& videoId);
  void showAllPlaylists();
  void showPlaylist(const std::string& playlistName);
  void removeFromPlaylist(const std::string& playlistName, const std::string& videoId);
  void clearPlaylist(const std::string& playlistName);
  void deletePlaylist(const std::string& playlistName);
  void searchVideos(const std::string& searchTerm);
  void searchVideosWithTag(const std::string& videoTag);
  void flagVideo(const std::string& videoId);
  void flagVideo(const std::string& videoId, const std::string& reason);
  void allowVideo(const std::string& videoId);
};
#pragma once

/** A class used to represent a Playlist */

class VideoPlaylist {};
Tutorial on C++ | Tutorial_on_C++_id |  #tutorial , #coding
DIY head scarf  | DIY_head_scarf_id |  #styling , #DIY
Endgame trailer | endgame_trailer_id |  #trailers , #entertainment
Life at Google  | life_at_google_video_id |  #google , #career
Video about nothing | nothing_video_id |
