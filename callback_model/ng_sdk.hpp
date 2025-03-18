#pragma once
#include <string>
#include <curl/curl.h>
#include <unordered_map>
#include <vector>
#include "./json.hpp"

class IMarketDataHandler {
public:
    virtual void OnPriceUpdate(const nlohmann::json& jsonData) = 0;
};

class ng_sdk {
public:
    void Initialize();
    void Subscribe(int instrument, IMarketDataHandler* subscriber);
    void publish(const nlohmann::json& jsonData);

private:
    int cnt = 0;
    std::unordered_map<int, std::vector<IMarketDataHandler*>> instrument_subscribers_list;
};
