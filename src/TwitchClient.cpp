#include "TwitchClient.hpp"
#include <iostream>

std::string TwitchClient::base_url = "https://api.twitch.tv/helix";

TwitchClient::TwitchClient(
    const std::string& bearer,
    const std::string& client_id
): m_bearer(bearer), m_client_id(client_id) {
}

TwitchClient::TwitchClient(): TwitchClient("", "") {
}

void TwitchClient::setBearer(const std::string& bearer) {
    m_bearer = bearer;
}

void TwitchClient::setClientId(const std::string& client_id) {
    m_client_id = client_id;
}

cpr::Response TwitchClient::fetch(const std::string& endpoint, const std::initializer_list<cpr::Parameter>& params) const {
    std::cout << "TwitchClient::fetch SANITY CHECK\n";

    if (m_bearer == "" || m_client_id == "") {
        throw std::invalid_argument("Either bearer or client id were empty strings");
    }

    std::string url = base_url + endpoint;
    std::cout << "url: " << url << '\n';

    cpr::Response r = cpr::Get(
        cpr::Url{url},
        cpr::Header {
            {"Authorization", "Bearer " + m_bearer},
            {"Client-Id", m_client_id}
        },
        cpr::Parameters(params)
    );

    std::cout << "After making get request\n";

    return r;
}
