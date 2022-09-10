#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<future>
#include<thread>
#include<functional>
#include<chrono>
#include<vector>
#include<sys/types.h>
#include<unistd.h>
#include<wait.h>
using namespace std;

void fun(promise<int> &p){
	this_thread::sleep_for(chrono::milliseconds(200));
	p.set_value(23);
}

class A{
	public:
		void fun(){
			cout<<"fun"<<endl;
		}
		void fun1(){
			thread t(&A::fun,this);
			t.join();
		}
};

void funnum(int num){
	sleep((rand()%100)/50);
	cout<<num<<endl;
}

int main(int argc,char **argv){
	pid_t pid;
	for(int i=0;i<100;i++){
		pid=fork();
		if(pid<0){
			perror("fork");

		}else if(pid==0){
			funnum(i);
			exit(0);
		}
	}
	for(int i=0;i<100;i++){
		wait(NULL);
	}
	return 0;
}
