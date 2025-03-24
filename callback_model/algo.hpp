#pragma once
#include "ng_sdk.hpp"

class Algo : public IMarketDataHandler {
public:
    Algo(long long int instrument);
    void OnPriceUpdate(PriceUpdate priceUpdate) override final;
    void start(ng_sdk& sdk_api);

private:
    long long int _instrument;
};
