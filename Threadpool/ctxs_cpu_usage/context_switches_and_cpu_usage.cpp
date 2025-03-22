// #include<iostream>
// #include<thread>
// #include<vector>
// #include<chrono>
// #include<sched.h>
// std::vector<std::thread> threads;
// void Func(){
//     long long int cnt=0;
//     std::cout<<"trying to initialize a thread"<<threads.size()<<std::endl;
//     while (true)
//     { 
//          std::cout<<std::hash<std::thread::id>()(std::this_thread::get_id())<<" "<<sched_getcpu() <<"     "<<threads.size()<<std::endl;
//     }
//     std::cout<<"thread created\n";
// }
// int main(){
//     long long int cnt=0;

//     while(cnt++<1){
//         try {
//             std::cout<<"going to create thread "<<threads.size()<<std::endl;
//             std::thread t1(Func);
//             threads.emplace_back(std::move(t1));
//         } catch (const std::system_error& e) {
//             std::cerr << "Thread creation failed: " << e.what() << std::endl;
//         } 
//     }
//     while (true)
//     {
//         /* code */
//     }
    
//     for (auto& t : threads) {
//         t.join();
//     }
//     return 0;
// }

#define _GNU_SOURCE
#include <iostream>
#include <thread>
#include <vector>
#include <sched.h>
#include <unistd.h>

// Function to pin a thread to a specific CPU
void pinThreadToCPU(int cpu) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(cpu, &cpuset);
    sched_setaffinity(0, sizeof(cpu_set_t), &cpuset);
}

// CPU-bound function that runs indefinitely
void busyLoop(int cpu_id) {
    pinThreadToCPU(cpu_id); // Pin to the specified logical CPU
    std::cout << "Thread " << std::this_thread::get_id() << " running on CPU " << cpu_id << std::endl;
    while (true) {
    } // Infinite loop
}

int main() {
    // Change these values to two logical cores of the same physical core
    int cpu1 = 0; // Logical core 1
    int cpu2 = 1; // Logical core 2 (same physical core as cpu1)

    std::thread t1(busyLoop, cpu1);
    std::thread t2(busyLoop, cpu2);

    t1.join();
    t2.join();

    return 0;
}
