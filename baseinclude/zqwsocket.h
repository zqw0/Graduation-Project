#ifndef ZQWSOCKET_H
#define ZQWSOCKET_H
/*
封装socket
*/
#include<arpa/inet.h>
#include<sys/socket.h>
#include<string>
#include<string.h>
#include<unistd.h>
namespace Zqw
{
    class ClntSock
    {
    private:
        int _fd;
        sockaddr_in _addr;
    public:
        ClntSock(/* args */) = delete;
        ClntSock(int op);
        ClntSock(int fd, sockaddr_in addr);
        int ClntConnect(std::string ip, int port);
        ~ClntSock();
    };
    class ServerSock{
    private:
        int _fd;
        int _op;
        sockaddr_in _addr;
    public:
        ServerSock() = delete;
        ServerSock(int sockop);
        int ServerBind(int port);
        int ServerListen(int PeopleTotal);
        ClntSock ServerAccept();
        ~ServerSock();
    };
}
#endif