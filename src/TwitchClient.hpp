#include <string>
#include <exception>
#include <initializer_list>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

class TwitchClient {
    public:
        TwitchClient(const std::string& bearer, const std::string& client_id);
        TwitchClient();
        void setBearer(const std::string& bearer);
        void setClientId(const std::string& client_id);
        cpr::Response fetch(const std::string& endpoint, const std::initializer_list<cpr::Parameter>& params) const;
    protected:
        static std::string base_url;
        std::string m_bearer;
        std::string m_client_id;
};
