#include "ICEOrderProcessor.h"

void ICEOrderInterface::sendOrder(){
    std::cout<<"Sending order to ICE"<<std::endl;
}

void ICEOrderInterface::cancelOrder(){
    std::cout<<"Cancelling order to ICE"<<std::endl;
}

void ICEOrderInterface::modifyOrder(){
    std::cout<<"Modifying order to ICE"<<std::endl;
}

void ICEOrderInterface::getOrderStatus(){
    std::cout<<"Getting order status from ICE"<<std::endl;
}

void ICEOrderInterface::getTradeStatus(){
    std::cout<<"Getting trade status from ICE"<<std::endl;
}

void ICEOrderInterface::getQuote(){
    std::cout<<"Getting quote from ICE"<<std::endl;
}