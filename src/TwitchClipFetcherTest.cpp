#include "TwitchClipFetcher.hpp"

#include <iostream>

int main() {
    std::map<std::string, std::string> credentials;
    std::string line;

    std::ifstream env("env.local");
    while (std::getline(env, line)) {
        size_t pos = line.find('=');
        credentials[line.substr(0, pos)] = line.substr(pos + 1);
    }

    TwitchClient tc = TwitchClient(credentials["access_token"], credentials["client_id"]);
    TwitchClipFetcher tcf = TwitchClipFetcher(tc);

    tcf.setBroadcasterIdFromStreamerHandle("supertf");
    std::cout << "broadcaster_id: " << tcf.getBroadcasterId() << '\n';

    std::pair<std::string, double> p = tcf.fetchRandomClip();
    std::cout << "clip name, duration: " << p.first << ", " << p.second << '\n';

    delete tc;

    return 0;
}
