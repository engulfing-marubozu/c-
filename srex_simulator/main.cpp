#include <iostream>
#include <string>

// Base Class
class ECBaseData {
protected:
    std::string exchangeTime;
    int sequenceNumber;

public:
    ECBaseData(const std::string& time, int seqNum)
        : exchangeTime(time), sequenceNumber(seqNum) {}

    virtual void display() const {
        std::cout << "Exchange Time: " << exchangeTime << "\n"
                  << "Sequence Number: " << sequenceNumber << std::endl;
    }

    virtual ~ECBaseData() = default;
};

// Unified Class for Both Requests and Responses
class ECRequestResponse : public ECBaseData {
protected:
    std::string messageType; // Holds type of message (e.g., "ECOrder", "ECAckedOrder", etc.)

public:
    ECRequestResponse(const std::string& time, int seqNum, const std::string& type)
        : ECBaseData(time, seqNum), messageType(type) {}

    void display() const override {
        ECBaseData::display();
        std::cout << "Message Type: " << messageType << std::endl;
    }
};

// Specific Class: ECOrder
class ECOrder : public ECRequestResponse {
    std::string orderDetails;

public:
    ECOrder(const std::string& time, int seqNum, const std::string& details)
        : ECRequestResponse(time, seqNum, "ECOrder"), orderDetails(details) {}

    void display() const override {
        ECRequestResponse::display();
        std::cout << "Order Details: " << orderDetails << std::endl;
    }
};

// Specific Class: ECAckedOrder
class ECAckedOrder : public ECRequestResponse {
    std::string ackMessage;

public:
    ECAckedOrder(const std::string& time, int seqNum, const std::string& message)
        : ECRequestResponse(time, seqNum, "ECAckedOrder"), ackMessage(message) {}

    void display() const override {
        ECRequestResponse::display();
        std::cout << "Acknowledgment Message: " << ackMessage << std::endl;
    }
};

int main() {
    // Create a request object for ECOrder
    ECOrder order("2025-01-16T10:00:00Z", 12345, "Buy 100 shares of AAPL");

    // Create a response object for ECAckedOrder
    ECAckedOrder ack("2025-01-16T10:01:00Z", 12346, "Order Accepted");

    // Display their details
    std::cout << "ECOrder Object:\n";
    order.display();

    std::cout << "\nECAckedOrder Object:\n";
    ack.display();

    return 0;
}
