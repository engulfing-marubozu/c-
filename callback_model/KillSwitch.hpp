#pragma once
#include <atomic>

class KillSwitch {
public:
    static KillSwitch& getInstance() {
        static KillSwitch instance;
        return instance;
    }

    bool isStopped() const {
        return stop_signal.load();
    }

    void stop() {
        stop_signal.store(true);
    }

private:
    KillSwitch() : stop_signal(false) {}
    std::atomic<bool> stop_signal;

    // Delete copy constructor and assignment operator
    KillSwitch(const KillSwitch&) = delete;
    KillSwitch& operator=(const KillSwitch&) = delete;
};
