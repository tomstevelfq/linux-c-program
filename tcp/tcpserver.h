#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include"../threadpool/threadpool.h"
using namespace std;

const string IP="0.0.0.0";
const int PORT=23456;
const int listenNum=50;
const int BUFFSIZE=4096;
class TcpServer{
    public:
        TcpServer():TcpServer(IP,PORT){}
        TcpServer(string ip,int port){
            servfd=socket(AF_INET,SOCK_STREAM,0);
            bzero(&servaddr,sizeof(sockaddr_in));
            inet_aton(ip.c_str(),&servaddr.sin_addr);
            servaddr.sin_port=htons(port);
            servaddr.sin_family=AF_INET;
            bind(servfd,(sockaddr*)&servaddr,sizeof(sockaddr_in));
            listen(servfd,listenNum);
        }
        void run(){
            sockaddr_in clientaddr;
            while(true){
                socklen_t len=sizeof(sockaddr_in);
                int clientfd=accept(servfd,(sockaddr*)&clientaddr,&len);
                pool.enqueue(bind(&TcpServer::response,this,clientfd,clientaddr));
            }
        }
        void response(int clientfd,sockaddr_in clientaddr){
            char *buff=new char[BUFFSIZE];
            bzero(buff,BUFFSIZE);
            recv(clientfd,buff,BUFFSIZE,0);
            cout<<"ip: "<<inet_ntoa(clientaddr.sin_addr)<<endl;
            cout<<"port: "<<ntohs(clientaddr.sin_port)<<endl;
            cout<<buff<<endl<<endl;
            strcat(buff,":server");
            send(clientfd,buff,strlen(buff),0);
            close(clientfd);
            delete(buff);
        }
    private:
        string ip;
        int port;
        sockaddr_in servaddr;
        int servfd;
        ThreadPool pool;
};