#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
using namespace std;

#define BUFFSIZE 4096
#define SERVER_PORT 44552
char buff[BUFFSIZE];
char sendbuf[BUFFSIZE];
int main(){
	struct sockaddr_in servaddr;
	struct sockaddr_in clientaddr;
	int servfd;
	servfd=socket(AF_INET,SOCK_DGRAM,0);
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(SERVER_PORT);
	bind(servfd,(struct sockaddr*)&servaddr,sizeof(struct sockaddr_in));
	socklen_t len=sizeof(struct sockaddr_in);
	cout<<"等待连接..."<<endl;
	while(true){
		recvfrom(servfd,buff,sizeof(buff),0,(struct sockaddr*)&clientaddr,&len);
		cout<<buff<<endl;
		bzero(sendbuf,strlen(sendbuf));
		strcat(sendbuf,"server:");
		strcat(sendbuf,buff);
		sendto(servfd,sendbuf,strlen(sendbuf)+1,0,(struct sockaddr*)&clientaddr,sizeof(struct sockaddr_in));
	}
	close(servfd);
	return 0;
}
