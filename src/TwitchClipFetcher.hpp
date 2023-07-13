#include <string>
#include <random>

#include "TwitchClient.hpp"

class TwitchClipFetcher {
    private:
        TwitchClient m_twitch_client;
        std::string m_broadcaster_id;
        static std::random_device m_rd;
        static std::mt19937 m_rng;
        static std::uniform_real_distribution<> m_uid;
    public:
        TwitchClipFetcher(const TwitchClient& twitch_client);
        TwitchClipFetcher(const TwitchClient& twitch_client, std::string broadcaster_id);
        std::string getBroadcasterId();
        void setBroadcasterId(std::string broadcaster_id);
        void setBroadcasterIdFromStreamerHandle(std::string streamer);
        std::pair<std::string, double> fetchRandomClip(int num_clips = 100);
};
