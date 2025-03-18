#pragma once
#include "ng_sdk.hpp"

class Algo : public IMarketDataHandler {
public:
    Algo(int instrument);
    void OnPriceUpdate(const nlohmann::json& jsonData) override final;
    void start(ng_sdk& sdk_api);

private:
    int _instrument;
};
