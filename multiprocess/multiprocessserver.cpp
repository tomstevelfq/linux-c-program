#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
using namespace std;

#define PORT 1234
#define QLEN 10
#define BUFFSIZE 4096
void sigchld(int);
void process_cli(int connectfd,sockaddr_in client);

int main(){
    int listenfd,connectfd;
    pid_t pid;
    sockaddr_in server,client;
    socklen_t len;
    if((listenfd=socket(AF_INET,SOCK_STREAM,0))==-1){
        perror("create socket error");
        exit(1);
    }
    bzero(&server,sizeof(sockaddr_in));
    server.sin_family=AF_INET;
    server.sin_port=htons(PORT);
    server.sin_addr.s_addr=htonl(INADDR_ANY);
    if(bind(listenfd,(sockaddr*)&server,sizeof(sockaddr_in))==-1){
        perror("bind socket");
        exit(1);
    }
    len=sizeof(sockaddr_in);
    signal(SIGCHLD,sigchld);
    while(1){
        if((connectfd=accept(listenfd,(sockaddr*)&client,&len))==-1){
            perror("accept error");
            exit(1);
        }
        if((pid=fork())>0){
            close(connectfd);
        }else if(pid==0){
            close(listenfd);
            process_cli(connectfd,client);
            exit(0);
        }else{
            perror("fork");
            exit(1);
        }
    }
    return 0;
}