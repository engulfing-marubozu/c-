#include "orsEngine.h"
#include "ICEOrderProcessor.h"
#include "CMEOrderProcessor.h"
#include "error_code.h"

ors::error_code orsEngine::Init(Config *cfg) {
    std::string exchange = cfg->exchange;
    if (exchange == "ICE") {
        orderInterface = new ICEOrderInterface();
    }
    else if(exchange == "CME") {
            if (exchange == "CME") {
        orderInterface = new CMEOrderInterface();
    }
    } else {
        return ors::error_code :: FAILURE;
    }
    std::cout << "Order Simulator Engine Initialized." << std::endl;
    return ors:: error_code :: SUCCESS;
}

void orsEngine::sendOrder() {
    orderInterface->sendOrder();
}

void orsEngine::cancelOrder() {
    orderInterface->cancelOrder();
}

void orsEngine::modifyOrder() {
    orderInterface->modifyOrder();
}

void orsEngine::getOrderStatus() {
    orderInterface->getOrderStatus();
}

void orsEngine::getTradeStatus() {
    orderInterface->getTradeStatus();
}

void orsEngine::getQuote() {
    orderInterface->getQuote();
}