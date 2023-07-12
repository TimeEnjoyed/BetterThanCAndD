#include <string>
#include <initializer_list>

#include <cpr/cpr.h>

class TwitchClient {
    public:
        TwitchClient(const std::string& bearer, const std::string& client_id);
        cpr::Response fetch(const std::string& endpoint, const std::initializer_list<cpr::Parameter>& params);
    protected:
        static std::string base_url;
        std::string m_bearer;
        std::string m_client_id;
};
