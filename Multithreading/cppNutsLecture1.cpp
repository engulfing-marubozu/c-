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
     
