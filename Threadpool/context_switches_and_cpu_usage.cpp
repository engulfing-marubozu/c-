#include<iostream>
#include<thread>
#include<vector>
#include<chrono>
#include<sched.h>
std::vector<std::thread> threads;
void Func(){
    long long int cnt=0;
    std::cout<<"trying to initialize a thread"<<threads.size()<<std::endl;
    while (true)
    { 
         std::cout<<std::hash<std::thread::id>()(std::this_thread::get_id())<<" "<<sched_getcpu() <<"     "<<threads.size()<<std::endl;
    }
    std::cout<<"thread created\n";
}
int main(){
    long long int cnt=0;

    while(cnt++<1){
        try {
            std::cout<<"going to create thread "<<threads.size()<<std::endl;
            std::thread t1(Func);
            threads.emplace_back(std::move(t1));
        } catch (const std::system_error& e) {
            std::cerr << "Thread creation failed: " << e.what() << std::endl;
        } 
    }
    while (true)
    {
        /* code */
    }
    
    for (auto& t : threads) {
        t.join();
    }
    return 0;
}