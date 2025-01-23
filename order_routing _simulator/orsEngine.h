#pragma once

#include <iostream>
#include "IOrderInterface.h"
#include "error_code.h"
#include "config.h"
class orsEngine {
public:
    ors::error_code Init(Config *cfg);
    void sendOrder();
    void cancelOrder();
    void modifyOrder();
    void getOrderStatus();
    void getTradeStatus();
    void getQuote();
private:
    IOrderInterface *orderInterface = nullptr;;
};

