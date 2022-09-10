#include<iostream>
#include<sys/socket.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#define PORT 23456
#define QLEN 10
#define BUFFSIZE 4096
using namespace std;

void sig_chld(int);
void process_cli(int connectfd,sockaddr_in client);

int main(){
    int listenfd,connectfd;
    pid_t pid;
    struct sockaddr_in server;
    struct sockaddr_in client;
    socklen_t ssize;
    if((listenfd=socket(AF_INET,SOCK_STREAM,0))==-1){
        perror("creating socket failed");
        exit(1);
    }
    bzero(&server,sizeof(sockaddr_in));
    server.sin_family=AF_INET;
    server.sin_port=htons(PORT);
    server.sin_addr.s_addr=htonl(INADDR_ANY);
    if(bind(listenfd,(sockaddr*)&server,sizeof(sockaddr_in))==-1){
        perror("bind error");
        exit(1);
    }
    if(listen(listenfd,QLEN)==-1){
        perror("listen error");
        exit(1);
    }
    ssize=sizeof(sockaddr_in);
    signal(SIGCHLD,sig_chld);
    
    return 0;
}