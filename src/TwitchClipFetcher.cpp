#include "TwitchClipFetcher.hpp"

std::random_device TwitchClipFetcher::m_rd;
std::mt19937 TwitchClipFetcher::m_rng(TwitchClipFetcher::m_rd());
std::uniform_real_distribution<> TwitchClipFetcher::m_uid(0, 1.0);

TwitchClipFetcher::TwitchClipFetcher(
    const TwitchClient& twitch_client,
    const std::string& broadcaster_id
): m_twitch_client(twitch_client), m_broadcaster_id(broadcaster_id) {
}

TwitchClipFetcher::TwitchClipFetcher(const TwitchClient &twitch_client): TwitchClipFetcher(twitch_client, "") {
}

std::string TwitchClipFetcher::getBroadcasterId() const {
    return m_broadcaster_id;
}

void TwitchClipFetcher::setBroadcasterId(const std::string& broadcaster_id) {
    std::cout << "setBroadcasterId called, broadcaster_id = " << broadcaster_id << '\n';
    m_broadcaster_id = broadcaster_id;
    std::cout << "setBroadcasterId called, m_broadcaster_id = " << m_broadcaster_id << '\n';
}

void TwitchClipFetcher::setBroadcasterIdFromStreamerHandle(const std::string& streamer) {
    const cpr::Response r = m_twitch_client.fetch(
        "/users",
        {{ "login", streamer }}
    );

    std::cout << "In TwitchClipFetcher::setBroadcasterIdFromStreamerHandle, r.text is: " << r.text << '\n';

    nlohmann::json streamer_data = nlohmann::json::parse(r.text);

    if (!streamer_data["data"].empty()) {
        setBroadcasterId(streamer_data["data"][0]["id"]);
    }
}

/**
 * \brief fetches random clip using Twitch api
 */
std::pair<std::string, double> TwitchClipFetcher::fetchRandomClip(int num_clips) {
    std::cout << "In TwitchClipFetcher SANITY CHECK\n";

    if (num_clips < 0 || 100 < num_clips) {
        throw std::domain_error("num_clips must be between 0 and 100");
    }

    if (m_broadcaster_id == "") {
        throw std::invalid_argument("Broadcaster id is empty");
    }

    std::cout << "Before fetching response\n";
    std::cout << "m_broadcaster_id: " << m_broadcaster_id << '\n';

    const cpr::Response r = m_twitch_client.fetch(
        "/clips",
        {
            { "broadcaster_id", m_broadcaster_id },
            { "first", "100" }
        }
    );

    std::cout << "After fetching response\n";
    // Needs try catch statement for exception
    nlohmann::json clip_data = nlohmann::json::parse(r.text);
    num_clips = std::min(num_clips, (int) clip_data["data"].size());

    std::cout << "num_clips: " << num_clips << '\n';

    int ndx = (int) lround(m_uid(m_rng) * num_clips);

    auto clip = clip_data["data"][ndx];

    return make_pair(clip["embed_url"], (double) clip["duration"]);
}
