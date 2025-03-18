// how threading is done in c++ and saves time 1️⃣

// #include<iostream>
// #include<chrono>
// #include<thread>
// #include<mutex>
// typedef long long int ll;

// void getEven(ll n, ll &even){
//     ll local_even=0;
//     for(ll i = 0; i <= n; i+=2){
//         local_even ++;
//     }
//     even = local_even;
// }

// void getOdd(ll n, ll &odd){
//     ll local_odd=0;
//     for(ll i = 1; i <= n; i+=2){
//         local_odd ++;
//     }
//     odd = local_odd;
// }
// int main(){
//     ll odd=0;
//     ll even=0;
//     ll start=0, end=1000000000;
//     auto start_time = std::chrono::high_resolution_clock::now();

//     // //applying threads
//     // getEven(end,std::ref(even)); // 500000000
//     // getOdd(end,std::ref(odd)); // 500000000
//     std::thread t1(getEven, end, std::ref(even));
//     std::thread t2(getOdd, end, std::ref(odd));
//     t1.join();
//     t2.join();
//     auto end_time = std::chrono::high_resolution_clock::now();
//     auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
//     std::cout << "Even: " << even << std::endl;
//     std::cout << "Odd: " << odd << std::endl;
//     std::cout << "Time taken: " << duration.count() << std::endl;
//     return 0;
// }

// // Even: 500000001
// // Odd: 500000000
// // Time taken: 158215


// // Even: 500000001
// // Odd: 500000000
// // Time taken: 320145


// // threads and process are two different things
// // threads are light weight process which share the same memory space and resources while process have their own memory space and resources which communicate with each other using IPC (Inter Process Communication) mechanism which makes them slower than threads.


///-------------------------------------------------------------------------------------------------------------------------------------------------------------------
// how race condition is happens in c++ 2️⃣
// #include<iostream>
// #include<chrono>
// #include<thread>
// #include<mutex>
// typedef long long int ll;

// void getEven(ll n, ll &even){
//     ll local_even=0;
//     for(ll i = 0; i <= n; i+=2){
//         even ++;
//     }
// }
// int main(){
//     ll even=0;
//     ll start=0, end=1000000000;
//     auto start_time = std::chrono::high_resolution_clock::now();

//     std::thread t1(getEven, end, std::ref(even));
//     std::thread t2(getEven, end, std::ref(even));
//     t1.join();
//     t2.join();
//     auto end_time = std::chrono::high_resolution_clock::now();
//     auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
//     std::cout << "Even: " << even << std::endl;
//     // std::cout << "Odd: " << odd << std::endl;
//     // std::cout << "Time taken: " << duration.count() << std::endl;
//     return 0;
// }

// case of race condition when two threads are trying to access the same resource at the same time
// to avoid
// 1. mutex
// 2. semaphore
// 3. condition variable
// 4. atomic variable   


// -------------------------------------------------------------------------------------------------------------------------------------------------------------------


// how to avoid race condition using mutex 3️⃣

// #include<iostream>
// #include<chrono>
// #include<thread>
// #include<mutex>
// typedef long long int ll;
// std::mutex m;
// void getEven(ll n, ll &even){
//     for(ll i = 0; i <= n; i+=2){
//         m.lock();
//         even ++;
//         m.unlock();
//     }
// }
// int main(){
//     ll even=0;
//     ll start=0, end=100000;
//     auto start_time = std::chrono::high_resolution_clock::now();

//     std::thread t1(getEven, end, std::ref(even));
//     std::thread t2(getEven, end, std::ref(even));
//     t1.join();
//     t2.join();
//     auto end_time = std::chrono::high_resolution_clock::now();
//     auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
//     std::cout << "Even: " << even << std::endl;
//     // std::cout << "Odd: " << odd << std::endl;
//     // std::cout << "Time taken: " << duration.count() << std::endl;
//     return 0;
// }


// ----------------------------------------------------------------------------------------------------------------------------------------
//use condition variable 🥵
// #include <iostream>
// #include <thread>
// #include <mutex>
// #include <condition_variable>

// std::mutex m;
// std::condition_variable cv;
// bool dataReady = false;  // Shared condition

// void producer() {
//     std::this_thread::sleep_for(std::chrono::seconds(1));  // Simulating work
//     std::lock_guard<std::mutex> lock(m);
//     dataReady = true;  // ✅ Set condition
//     std::cout << "Producer: Data is ready!\n";
//     cv.notify_one();  // ✅ Notify consumer
// }

// void consumer() {
//     std::unique_lock<std::mutex> lock(m);
//     // cv.wait(lock, [] { return dataReady; });  // ✅ Wait until condition is true
//     while (!dataReady) {
//         cv.wait(lock);  
//     }    
//     // if(!dataReady){
//     //     cv.wait(lock);   this is wrong, as will not be able to handle spurous wakeups
//     // }
//     std::cout << "Consumer: Processing data...\n";
// }

// int main() {
//     std::thread t1(producer);
//     std::thread t2(consumer);
//     t1.join();
//     t2.join();
// }

// cv.wait(lock, [] { return dataReady; });   if dataReady is false then it wiill free up the lock and sleep and wait for the wakeup signal
// if dataReady is true then it will not sleep and continue the execution

//------------------------------------------------------------------------------------------------------------------------------------------------------------
//SUPERSCALING (one step better from hyperthreading) 😲
// #include <iostream>
// #include <thread>
// #include <sched.h>  // For setting CPU affinity
// #include <unistd.h> // For getting CPU count

// void set_cpu_affinity(int core_id) {
//     cpu_set_t cpuset;
//     CPU_ZERO(&cpuset);
//     CPU_SET(core_id, &cpuset);
    
//     int rc = sched_setaffinity(0, sizeof(cpu_set_t), &cpuset);
//     if (rc != 0) {
//         std::cerr << "Error setting CPU affinity\n";
//     }
// }

// void alu_task() {
//     set_cpu_affinity(0);  // Bind to core 2
//     int x = 0;
//     for (long long i = 0; i < 1e9; i++) {
//         x += i % 2;  // ALU-heavy (Integer operations)
//     }
//     std::cout << "Alu Thread-> " << std::hash<std::thread::id>{}(std::this_thread::get_id())<< " is running on Core " << sched_getcpu()  << std::endl;
//     std::cout << "ALU Task Done\n";
// }

// void fpu_task() {
//     set_cpu_affinity(1);  // Bind to the same core 2
//     double y = 0.0;
//     for (long long i = 0; i < 1e9; i++) {
//         y += 0.1 * i;  // FPU-heavy (Floating-point operations)
//     }
//     std::cout << "FPU THREAD-> " << std::hash<std::thread::id>{}(std::this_thread::get_id())<< " is running on Core " << sched_getcpu()  << std::endl;
//     std::cout << "FPU Task Done\n";
// }

// int main() {
//     std::thread t1(alu_task);
//     std::thread t2(alu_task);
//     t1.join();
//     t2.join();
// }

// // 1. Superscalar processors can issue multiple instructions per cycle using different functional units (e.g., ALU, FPU, Load/Store).
// // 2. If one thread uses ALU while the other thread uses FPU, both execution units operate in parallel, enabling overall CPU usage to exceed 100%.
// // To test this, we need to pin the thread execution to a perticular logical core pair. 
// // superscaling is the reason why cpu core pair usage exceeds 100% when seen using htop.
// // [root@JPR-2YJCVQ3 c-]# lscpu --extended
// // CPU SOCKET CORE L1d:L1i:L2:L3 ONLINE
// //   0      0    0 0:0:0:0          yes
// //   1      0    0 0:0:0:0          yes
// //   2      0    1 1:1:1:0          yes
// //   3      0    1 1:1:1:0          yes
// //   4      0    2 2:2:2:0          yes
// //   5      0    2 2:2:2:0          yes
// //   6      0    3 3:3:3:0          yes
// //   7      0    3 3:3:3:0          yes
// //   8      0    4 4:4:4:0          yes
// //   9      0    4 4:4:4:0          yes
// //  10      0    5 5:5:5:0          yes
// //  11      0    5 5:5:5:0          yes
// //  12      0    6 6:6:6:0          yes
// //  13      0    6 6:6:6:0          yes
// //  14      0    7 7:7:7:0          yes
// //  15      0    7 7:7:7:0          yes
// //  16      0    8 8:8:8:0          yes
// //  17      0    8 8:8:8:0          yes
// //  18      0    9 9:9:9:0          yes
// //  19      0    9 9:9:9:0          yes
