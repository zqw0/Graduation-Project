#include "zqwsocket.h"
namespace Zqw{
    ClntSock::ClntSock(int op){
        _fd = socket(PF_INET, op, 0);
    }
    ClntSock::ClntSock(int fd, sockaddr_in addr){
        _fd = fd;
        _addr = addr;
    }
    int ClntSock::ClntConnect(std::string ip, int port){
        memset(&_addr, 0, sizeof(_addr));
        _addr.sin_addr.s_addr = inet_addr(ip.c_str());
        _addr.sin_family = AF_INET;
        _addr.sin_port = htons(port);
        return connect(_fd, (sockaddr*)&_addr, sizeof(_addr));
    }
    ClntSock::~ClntSock(){
        close(_fd);
    }
    ServerSock::ServerSock(int op){
        _fd = socket(PF_INET, op, 0);
    }
    int ServerSock::ServerBind(int port){
        memset(&_addr, 0, sizeof(_addr));
        _addr.sin_port = htons(port);
        _addr.sin_family = AF_INET;
        _addr.sin_addr.s_addr = htonl(INADDR_ANY);
        return bind(_fd, (sockaddr*)&_addr, sizeof(_addr));
    }
    int ServerSock::ServerListen(int TotalPeople){
        return listen(_fd, TotalPeople);
    }
    ClntSock ServerSock::ServerAccept(){
        sockaddr_in clnt_addr;
        memset(&clnt_addr, 0, sizeof(clnt_addr));
        socklen_t clnt_size = sizeof(clnt_addr);
        int clntfd = accept(_fd, (sockaddr*)&clnt_addr, &clnt_size);
        return ClntSock(clntfd, clnt_addr);
    }
    ServerSock::~ServerSock(){
        close(_fd);
    }
    
}