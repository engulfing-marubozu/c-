#include<iostream>
#include<thread>
#include<vector>
#include<queue>
#include<mutex>
#include<condition_variable>
#include<functional>
#include<csignal>
#include<atomic>

std::atomic<bool> stop_signal{false};
void signalHandler(int signum) {
    if (signum == SIGINT) {
        std::cout << "\nCtrl+C detected! Stopping...\n";
        stop_signal = true;
    }
}

void task(){
    long long int cnt =0;
    std:: cout<<"task executed";
    // while(cnt++<1000){
    //     std::cout<<std::hash<std::thread::id>()(std::this_thread::get_id())<<" "<<sched_getcpu() <<"     "<<std::endl;
    // }
    while(true){
        
    }
};
class Threadpool{
    public:
    Threadpool(int num_threads):num_threads(num_threads){
        for(int i=0 ; i < num_threads ; i++){
            threads.emplace_back([this] {
                while (1) {
                    {
                        std::unique_lock<std::mutex> lock(m);  
                        cv.wait(lock, [this] { return !tasks.empty() || stop_signal; });
                
                        if (stop_signal) {
                            std::cout << "Thread exiting gracefully\n";
                            return;
                        }
                        std::cout<<"picing a task\n";
                        std::function<void()> task = std::move(tasks.front());
                        tasks.pop();
    
                    }
                    task();
                    std::cout<<"finished taks\n";
                }
            });
                   
        }
    };
    ~Threadpool() {
        {
            std::lock_guard<std::mutex> lock(m);
            stop_signal = true;  
        }
        cv.notify_all();  // to wake up all so that the infinite running threads can stop looking for new tasks and break the loop.
    
        for (auto &thread : threads) {
            if (thread.joinable()) {
                thread.join();
                std::cout << "Destructor: Thread joined\n";
            }
        }
    }
    
    void executeTask(std::function<void()> task){
          m.lock();
          tasks.push(task);
          m.unlock();
          cv.notify_all();
    }
    private : 
    int num_threads;
    std::queue<std::function <void()>> tasks;
    std::vector<std::thread> threads;
    std::mutex m;
    std::condition_variable cv;   
};

int main(){
    signal(SIGINT, signalHandler);
    Threadpool pool(3);
    int cnt=0;

    while(cnt++<3){
       pool.executeTask(task);  
    };
    while (!stop_signal)
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }    
    return 0;
}
