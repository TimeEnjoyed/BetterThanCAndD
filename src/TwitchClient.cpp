#include "TwitchClient.hpp"
#include <iostream>

std::string TwitchClient::base_url = "https://api.twitch.tv/helix";

TwitchClient::TwitchClient(
    const std::string& bearer,
    const std::string& client_id
): m_bearer(bearer), m_client_id(client_id) {
}

cpr::Response TwitchClient::fetch(const std::string& endpoint, const std::initializer_list<cpr::Parameter>& params) {
    std::string url = base_url + endpoint;
    cpr::Response r = cpr::Get(
        cpr::Url{url},
        cpr::Header {
            {"Authorization", "Bearer " + m_bearer},
            {"Client-Id", m_client_id}
        },
        cpr::Parameters(params)
    );

    return r;
}
