#pragma once

#include<iostream>
#include "IOrderInterface.h"
class ICEOrderInterface : public IOrderInterface{
    public :
      void sendOrder() override;
      void cancelOrder() override;
      void modifyOrder() override;
      void getOrderStatus() override;
      void getTradeStatus() override;
      void getQuote() override;  
};
