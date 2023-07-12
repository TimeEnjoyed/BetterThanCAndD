
class TwitchClipFetcher {
    private:
        std::string get_broadcaster_id(std::string streamer);
    public:
        std::string fetch_clip(std::string streamer);
};
