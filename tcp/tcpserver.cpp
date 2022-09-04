#include<iostream>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
#define BUFFSIZE 4096
#define SERVER_PORT 23456
char buff[BUFFSIZE];

int main(){
    struct sockaddr_in servaddr,clientaddr;
    int servfd,clientfd;
    servfd=socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof(struct sockaddr_in));
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(SERVER_PORT);
    bind(servfd,(struct sockaddr*)&servaddr,sizeof(struct sockaddr_in));
    listen(servfd,20);
    socklen_t len=sizeof(struct sockaddr_in);
    cout<<"等待连接..."<<endl;
    while(true){
        clientfd=accept(servfd,(struct sockaddr*)&clientaddr,&len);
        bzero(buff,strlen(buff));
        recv(clientfd,buff,sizeof(buff),0);
        //recvfrom(clientfd,buff,sizeof(buff),0,0,0);
        cout<<"ip: "<<inet_ntoa(clientaddr.sin_addr)<<endl;
        cout<<"port: "<<ntohs(clientaddr.sin_port)<<endl;
        cout<<buff<<endl<<endl;
        strcat(buff,":server");
        send(clientfd,buff,strlen(buff),0);
        close(clientfd);
    }
    close(servfd);
    return 0;
}