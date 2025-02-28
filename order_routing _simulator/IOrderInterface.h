#pragma once
#include<iostream>

class IOrderInterface{
    public:
    virtual void sendOrder() = 0;
    virtual void cancelOrder() = 0;
    virtual void modifyOrder() = 0;
    virtual void getOrderStatus() = 0;
    virtual void getTradeStatus() = 0;
    virtual void getQuote() = 0;
};
