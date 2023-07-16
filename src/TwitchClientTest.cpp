#include <iostream>
#include <sstream>
#include <map>
#include "TwitchClient.hpp"

int main() {
    std::map<std::string, std::string> credentials;
    std::string line;

    std::ifstream env("env.local");
    while (std::getline(env, line)) {
        size_t pos = line.find('=');
        credentials[line.substr(0, pos)] = line.substr(pos + 1);
    }

    TwitchClient tc = TwitchClient(credentials["access_token"], credentials["client_id"]);
    cpr::Response r = tc.fetch("/clips", {{ "id", "123456" }});

    std::cout << r.status_code << '\n';
    std::cout << r.text;
}
