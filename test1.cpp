#include<unistd.h>
#include<stdio.h>
#include<iostream>
#include<sys/types.h>
#include<wait.h>
#include<math.h>
#include<thread>
#include<functional>
#include<string.h>
#include<signal.h>
using namespace std;

class A{
    public:
        A(){
            cout<<"A构造"<<endl;
        }
        ~A(){
            cout<<"A xogou"<<endl;
        }
};

class B{
    public:
        B(){
            cout<<"b gouzao"<<endl;
        }
        ~B(){
            cout<<"B xigou"<<endl;
        }
        A a;
};

int pfun(int a){
    cout<<a<<endl;
    return a;
}

int (*ff(int a))(int){
    cout<<a<<endl;
    return pfun;
}

void sigintfun(int){
    pid_t pid;
    while((pid=wait(NULL))>0){
        cout<<"son process "<<pid<<endl;
    }
    return;
}
void sigalrm(int){
    cout<<"alarm"<<endl;
}
void sigalrm1(int){
    cout<<"alarm1"<<endl;
}
void son(){
    sleep(1);
    cout<<"I am son "<<getpid()<<"  "<<getppid()<<endl;
}

struct AA{
    int a;
};

int main(){
    // pid_t pid;
    // int *a=new int(88);
    // cout<<"begin:"<<*a<<endl;
    // signal(SIGCHLD,sigintfun);
    // for(int i=0;i<10;i++){
    //     pid=fork();
    //     if(pid<0){
    //         perror("fork");
    //         exit(1);
    //     }else if(pid==0){
    //         son();
    //         exit(0);  //子进程结束
    //     }
    // }
    // sleep(2);
    // cout<<"main process done"<<getpid()<<endl;
    // alarm(5);
    // signal(SIGALRM,sigalrm);
    // signal(SIGALRM,sigalrm1);
    // pause();
    // cout<<"end"<<endl;
    // double ff=1.0;
    // float f=ff+1;
    AA aa;
    aa.a=23;
    cout<<aa.a<<endl;
    return 0;
}