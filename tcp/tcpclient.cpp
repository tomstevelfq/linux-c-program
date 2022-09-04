#include<iostream>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
using namespace std;
#define BUFFSIZE 4096
#define SERVER_PORT 23456
char buff[BUFFSIZE];

int main(){
    string servip="127.0.0.1";
    struct sockaddr_in servaddr;
    int clientfd;
    clientfd=socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof(struct sockaddr_in));
    servaddr.sin_family=AF_INET;
    inet_aton(servip.c_str(),&servaddr.sin_addr);
    servaddr.sin_port=htons(SERVER_PORT);
    cout<<"发送消息:"<<endl;
    int res=connect(clientfd,(struct sockaddr*)&servaddr,sizeof(struct sockaddr_in));
    cin.getline(buff,sizeof(buff));
    send(clientfd,buff,strlen(buff),0);
    recv(clientfd,buff,sizeof(buff),0);
    cout<<buff<<endl;
    close(clientfd);
    return 0;
}