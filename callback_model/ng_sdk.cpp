#include "ng_sdk.hpp"
#include <iostream>
#include <thread>
#include <chrono>

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;
    std::string* str = static_cast<std::string*>(userp);
    str->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

void ng_sdk::Initialize() {
    while (true) {
        CURL* curl;
        CURLcode res;
        std::string readBuffer;

        curl_global_init(CURL_GLOBAL_DEFAULT);
        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, "https://jsonplaceholder.typicode.com/todos/1");
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

            res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            } else {
                try {
                    auto jsonData = nlohmann::json::parse(readBuffer);
                    std::cout << "Received JSON:" << std::endl;
                    cnt++;
                    publish(jsonData);
                } catch (const nlohmann::json::parse_error& e) {
                    std::cerr << "JSON parse error: " << e.what() << std::endl;
                }
            }
            curl_easy_cleanup(curl);
        }
        curl_global_cleanup();
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void ng_sdk::Subscribe(int instrument, IMarketDataHandler* subscriber) {
    std::cout << "Subscribed instrument " << instrument << std::endl;
    instrument_subscribers_list[instrument].push_back(subscriber);
}

void ng_sdk::publish(const nlohmann::json& jsonData) {
    std::cout << instrument_subscribers_list.size();
    for (auto& pair : instrument_subscribers_list) {
        if (cnt % pair.first == 0) {
            std::cout << "publishing to Algo " << pair.first << std::endl;
            for (auto& subscriber : pair.second) {
                subscriber->OnPriceUpdate(jsonData);
            }
        }
    }
}
