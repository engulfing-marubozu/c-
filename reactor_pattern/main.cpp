#include <iostream>
#include <vector>
#include <memory>
#include <thread>
#include <atomic>
#include <functional>
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>

// Simple WorkerThread class
class WorkerThread {
public:
    WorkerThread(const std::string &name = "")
        : name_(name), work_guard_(boost::asio::make_work_guard(io_context_)), finished_(false) {}

    ~WorkerThread() {
        Stop();
    }

    // Start the thread
    void Start() {
        finished_ = false;
        thread_ = std::thread(&WorkerThread::ThreadEntry, this);
    }

    // Stop the thread
    void Stop() {
        finished_ = true;
        work_guard_.reset();  // Let io_context stop when tasks are done
        io_context_.stop();   // Stop the io_context
        if (thread_.joinable()) {
            thread_.join();
        }
    }

    // Post a task to this thread
    void PostTask(const std::function<void()> &task) {
        io_context_.post(task);
    }

    // Get the number of tasks executed (for load-balancing demonstration)
    int GetTaskCount() const {
        return task_count_;
    }

private:
    void ThreadEntry() {
        while (!finished_) {
            try {
                io_context_.run(); // Run the io_context (process tasks)
                io_context_.reset(); // Reset after run completes
            } catch (const std::exception &e) {
                std::cerr << "Exception in WorkerThread " << name_ << ": " << e.what() << std::endl;
            }
        }
    }

    boost::asio::io_context io_context_;
    boost::asio::executor_work_guard<boost::asio::io_context::executor_type> work_guard_;
    std::thread thread_;
    std::atomic<bool> finished_;
    std::atomic<int> task_count_{0};
    std::string name_;
};

// Simple Distributor class
class TaskDistributor {
public:
    TaskDistributor(int num_threads) {
        for (int i = 0; i < num_threads; ++i) {
            auto worker = std::make_unique<WorkerThread>("Worker-" + std::to_string(i + 1));
            worker->Start();
            workers_.push_back(std::move(worker));
        }
    }

    ~TaskDistributor() {
        StopAll();
    }

    // Distribute a task (simple round-robin for load balancing)
    void DistributeTask(const std::function<void()> &task) {
        if (workers_.empty()) {
            std::cerr << "No worker threads available." << std::endl;
            return;
        }
        workers_[next_worker_]->PostTask(task);
        next_worker_ = (next_worker_ + 1) % workers_.size();
    }

    // Stop all workers
    void StopAll() {
        for (auto &worker : workers_) {
            worker->Stop();
        }
    }

private:
    std::vector<std::unique_ptr<WorkerThread>> workers_;
    size_t next_worker_{0}; // Round-robin counter
};

// Main function to demonstrate functionality
int main() {
    // Create a distributor with 3 worker threads
    TaskDistributor distributor(3);

    // Simulate distributing tasks
    for (int i = 0; i < 10; ++i) {
        distributor.DistributeTask([i]() {
            std::cout << "Processing task " << i + 1 << " on thread " << std::this_thread::get_id() << std::endl;
        });
    }

    // Allow some time for tasks to complete
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // Stop all worker threads
    distributor.StopAll();

    return 0;
}
