#include <string>
#include <random>
#include <iostream>

#include "TwitchClient.hpp"

class TwitchClipFetcher {
    private:
        const TwitchClient &m_twitch_client;
        std::string m_broadcaster_id;
        static std::random_device m_rd;
        static std::mt19937 m_rng;
        static std::uniform_real_distribution<> m_uid;
    public:
        TwitchClipFetcher(const TwitchClient &twitch_client);
        TwitchClipFetcher(const TwitchClient &twitch_client, const std::string& broadcaster_id);
        std::string getBroadcasterId() const;
        void setBroadcasterId(const std::string& broadcaster_id);
        void setBroadcasterIdFromStreamerHandle(const std::string& streamer);
        std::pair<std::string, double> fetchRandomClip(int num_clips = 100);
};
