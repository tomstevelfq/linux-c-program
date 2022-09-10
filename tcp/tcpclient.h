#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
using namespace std;

#define BUFFSIZE 4096
#define SERVER_PORT 23456
const string IP="127.0.0.1";
char buff[BUFFSIZE];
class TcpClient{
    public:
        TcpClient(){

        }
        TcpClient()
        void senddata(){}
    private:
        int clientfd;
};