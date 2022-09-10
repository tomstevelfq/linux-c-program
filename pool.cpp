#include<iostream>
#include<thread>
#include<queue>
#include<mutex>
#include<unistd.h>
using namespace std;

queue<int> q;
mutex loc;
void getnum(string id){
    while(!q.empty()){
        std::unique_lock<mutex> lock(loc);
        sleep(0.01);
        if(!q.empty()){
            cout<<id<<": "<<q.front()<<endl;
            q.pop();
        }
    }
}
int main(){
    for(int i=0;i<10000;i++){
        q.push(i);
    }
    thread t1(getnum,"thread 1");
    thread t2(getnum,"thread 2");
    thread t3(getnum,"thread 3");
    t1.join();
    t2.join();
    t3.join();
    return 0;
}