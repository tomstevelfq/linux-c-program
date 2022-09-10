#include<iostream>
#include<functional>
#include<thread>
#include<future>
using namespace std;

int fun1(int a){
    a++;
    return a;
}

int fun2(int a,int b){
    return a*b;
}

string fun3(){
    return "hello";
}

template<typename F,typename ...Args>
auto fun(F&& f,Args&& ...args)->future<decltype(f(args...))>{
    promise<decltype(f(args...))> p;
    future<decltype(f(args...))> fu=p.get_future();
    thread t([&]{
        p.set_value(f(args...));
    });
    t.join();
    return fu;
}

void funn(){
    cout<<"funn"<<endl;
}


int main(){
    future<int> f=fun(fun2,2,3);
    cout<<f.get()<<endl;
    future<string> f1=fun(fun3);
    cout<<f1.get()<<endl;
    return 0;
}