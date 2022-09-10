#include<iostream>
#include<thread>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
using namespace std;

#define BUFFSIZE 4096
#define SERVER_PORT 44552
char buff[BUFFSIZE];

int servfd;
int i=0;
void send_(sockaddr* addr){
    cout<<buff<<i++<<endl;
	sendto(servfd,buff,strlen(buff)+1,0,addr,sizeof(struct sockaddr_in));
}

int main(){
    struct sockaddr_in servaddr;
	struct sockaddr_in clientaddr;
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
        thread t(send_,(struct sockaddr*)&clientaddr);
        t.detach();
	}
	close(servfd);
    return 0;
}