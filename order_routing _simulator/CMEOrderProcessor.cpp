#include "CMEOrderProcessor.h"

void CMEOrderInterface::sendOrder(){
    std::cout<<"Sending order to CME"<<std::endl;
}

void CMEOrderInterface::cancelOrder(){
    std::cout<<"Cancelling order to CME"<<std::endl;
}

void CMEOrderInterface::modifyOrder(){
    std::cout<<"Modifying order to CME"<<std::endl;
}

void CMEOrderInterface::getOrderStatus(){
    std::cout<<"Getting order status from CME"<<std::endl;
}

void CMEOrderInterface::getTradeStatus(){
    std::cout<<"Getting trade status from CME"<<std::endl;
}

void CMEOrderInterface::getQuote(){
    std::cout<<"Getting quote from CME"<<std::endl;
}