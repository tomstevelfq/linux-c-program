#include<iostream>
#include<thread>
#include<functional>
#include<vector>
#include<queue>
#include<future>
#include<condition_variable>
#include<mutex>
#include<memory>
#include<stdexcept>
using namespace std;

#define NUM 10
class ThreadPool{
    public:
        ThreadPool():ThreadPool(NUM){}
        ThreadPool(int num){
            stop=false;
            for(int i=0;i<num;i++){
                works.emplace_back(
                    [this]{
                        for(;;){
                            function<void()> task;
                            {
                                unique_lock<mutex> lock(qmutex);
                                condition.wait(lock,[this]{return this->stop||!this->tasks.empty();});
                                if(stop&&tasks.empty()){
                                    return;
                                }
                                task=move(tasks.front());
                                tasks.pop();
                            }
                            task();
                        }
                    }
                );
            }
        }
        ~ThreadPool(){
            {
                unique_lock<mutex> lock(qmutex);
                stop=true;
            }
            condition.notify_all();
            for(auto& it:works){
                it.join();
            }
        }
        template<typename F,typename ...Args>
        auto enqueue(F&& f,Args&& ...args)->future<decltype(f(args...))>{
            using retype=decltype(f(args...));
            auto task=make_shared<packaged_task<retype()>>(packaged_task<retype()>(bind(forward<F>(f),forward<Args>(args)...)));
            future<retype> fu=task->get_future();
            tasks.push([task,this]{
                (*task)();
            });
            condition.notify_one();
            return fu;
        }
    private:
        queue<function<void()>> tasks;
        vector<thread> works;
        condition_variable condition;
        mutex qmutex;
        bool stop;
};