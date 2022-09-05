#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
using namespace std;
#define BUFFSIZE 4096
#define SERVER_PORT 44552
char buff[BUFFSIZE];
int main(){
    string servip="127.0.0.1";
    struct sockaddr_in servaddr;
    int clientfd;
    cout<<"发送消息:"<<endl;
    cin.getline(buff,sizeof(buff));
    clientfd=socket(AF_INET,SOCK_DGRAM,0);
    bzero(&servaddr,sizeof(struct sockaddr_in));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(SERVER_PORT);
    inet_aton(servip.c_str(),&servaddr.sin_addr);
    sendto(clientfd,buff,strlen(buff),0,(struct sockaddr*)&servaddr,sizeof(sockaddr_in));
    socklen_t len;
    recvfrom(clientfd,buff,sizeof(buff),0,(struct sockaddr*)&servaddr,&len);
    cout<<buff<<endl;
    close(clientfd);
    return 0;
}