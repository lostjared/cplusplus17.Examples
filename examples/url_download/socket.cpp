/*
 UNIX Socket class
 written by Jared Bruni
*/

#include "socket.hpp"

namespace net {
    
    Socket::Socket() : sockfd(0), addrlen(0), blocking(true) {
        
    }
    
    Socket::Socket(int fd) : sockfd(fd), addrlen(0), blocking(true) {
        
    }
    
    Socket::Socket(const Socket &s) {
        setSocket(s);
    }
    
    Socket::Socket(Socket &&s) {
        setSocket(s);
    }
    
    Socket &Socket::operator=(const Socket &s) {
        setSocket(s);
        return *this;
    }
    
    Socket &Socket::operator=(const Socket &&s) {
        setSocket(s);
        return *this;
    }
    
    void Socket::setSocket(const Socket &s) {
        sockfd = s.sockfd;
        addrlen = s.addrlen;
        blocking = s.blocking;
    }
    
    void Socket::setSocket(Socket &&s) {
        sockfd = std::move(s.sockfd);
        addrlen = std::move(s.addrlen);
        blocking = std::move(s.blocking);
    }
    
    int Socket::connectToIp(const std::string &host, const std::string &port, SocketType type) {
        addrinfo hints;
        addrinfo *rt, *rp;
        int sfd, s;
        memset(&hints, 0, sizeof(addrinfo));
        hints.ai_canonname = NULL;
        hints.ai_addr = NULL;
        hints.ai_next = NULL;
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = (type == SocketType::STREAM) ? SOCK_STREAM : SOCK_DGRAM;
        s = getaddrinfo(host.c_str(), port.c_str(), &hints, &rt);
        if(s != 0) {
            errno = ENOSYS;
            return -1;
        }
        for(rp = rt; rp != NULL; rp = rp->ai_next) {
            sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
            if(sfd == -1)
                continue;
            
            if(connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
                break;
            
            close(sfd);
        }
        
        if(rp != NULL) {
            this->sockfd = sfd;
            this->addrlen = rp->ai_addrlen;
        }
        freeaddrinfo(rt);
        return (rp == NULL) ? -1 : sfd;
    }
    
    int Socket::connectToIp(const std::string &hostname, int port) {
        sockfd = socket(AF_INET,SOCK_STREAM,0);
        if(sockfd == -1) {
            herror("socket");
            return -1;
        }
        struct sockaddr_in saddy;
        memset(&saddy, 0, sizeof(sockaddr_in));
        saddy.sin_port = htons(port);
        in_addr_t a = inet_addr(hostname.c_str());
        if(a == -1) {
            herror("inet_addr");
            return -1;
        }
        saddy.sin_addr.s_addr = a;
        saddy.sin_family = AF_INET;
        if(connect(sockfd, (const sockaddr*)&saddy, sizeof(sockaddr_in)) != -1) {
            return sockfd;
        }
        herror("connect");
        return -1;
    }
    
    int Socket::listenAt(const std::string &port, SocketType type, int backlog) {
        addrinfo hints;
        addrinfo *rt, *rp;
        int sfd, optval, s;
        memset(&hints, 0, sizeof(addrinfo));
        hints.ai_canonname = NULL;
        hints.ai_addr = NULL;
        hints.ai_next = NULL;
        hints.ai_socktype = (type == SocketType::STREAM) ? SOCK_STREAM : SOCK_DGRAM;
        hints.ai_family = AF_UNSPEC;
        hints.ai_flags = AI_PASSIVE;
        s = getaddrinfo(NULL, port.c_str(), &hints, &rt);
        if(s != 0)
            return -1;
        optval = 1;
        for(rp = rt; rp != NULL; rp = rp->ai_next) {
            sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
            if(sfd == -1)
                continue;
            
            if(setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1) {
                close(sfd);
                freeaddrinfo(rt);
                return -1;
            }
            
            if(bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
                break;
            
            close(sfd);
        }
        
        if(rp != NULL) {
            if(listen(sfd, backlog) == -1) {
                freeaddrinfo(rt);
                return -1;
            }
            this->sockfd = sfd;
            this->addrlen = rp->ai_addrlen;
        }
        freeaddrinfo(rt);
        return (rp == NULL) ? -1 : sfd;
    }
    
    ssize_t Socket::readLine(std::string &buf) {
        if(!valid()) return -1;
        ssize_t bytesRead = 0;
        while(1) {
            char c;
            ssize_t readVal = read(sockfd, &c, 1);
            if(readVal == 0 || readVal == -1) break;
            if(c == '\n') break;
            buf += c;
            bytesRead++;
        }
        return bytesRead;
    }
    
    ssize_t Socket::readHeader(std::string &buf) {
        if(!valid()) return -1;
        ssize_t bytesRead = 0;
        ssize_t readVal = 0;
        char c = 0;
        int count = 0;
        while(1) {
            readVal = read(sockfd, &c, 1);
            if(readVal == 0 || readVal == -1) break;
            buf += c;
            bytesRead++;
            if(buf.rfind("\r\n\r\n") != std::string::npos) break;
        }
        return bytesRead;
    }
    
    std::string Socket::readLine(ssize_t &bytesRead) {
        bytesRead = 0;
        std::ostringstream stream;
        while(1) {
            char c;
            ssize_t readVal = read(sockfd, &c, 1);
            if(readVal == 0 || readVal == -1) break;
            if(c == '\n') break;
            stream << c;
            bytesRead++;
            
        }
        return stream.str();
    }
    
    ssize_t Socket::receive(void *buf, size_t len) {
        return read(sockfd, buf, len);
    }
    
    ssize_t Socket::sendString(const std::string &text) {
        return sendData((const void*)text.c_str(), text.length());
    }
    
    ssize_t Socket::sendData(const void *buf, size_t len) {
        return write(sockfd, buf, len);
    }
    
    int Socket::closeSocket() {
        return close(sockfd);
    }
    
    int Socket::acceptSocket(Socket &s) {
        int newsock = accept(sockfd, 0, 0);
        if(newsock == -1) return -1;
        Socket sa(newsock);
        s = sa;
        return newsock;
    }
    
    int Socket::acceptSocket(Socket &s, sockaddr *addr, socklen_t *addrlen) {
        int newsock = accept(sockfd, addr, addrlen);
        if(newsock == -1) return -1;
        Socket sa(newsock);
        s = sa;
        return newsock;
    }
    
    void Socket::setBlocking(bool state) {
        if(sockfd >= 0) {
            int flags = fcntl(sockfd, F_GETFL);
            if(flags == -1) {
                std::cerr << "Error getting flags for: " << sockfd << "\n";
                return;
            }
            if(state == true) flags &= ~O_NONBLOCK;
            else flags |= O_NONBLOCK;
            blocking = state;
            if(fcntl(sockfd, F_SETFL, flags) == -1)
                std::cerr << "Error settings flags on: " << sockfd << "\n";
        }
    }
    
    void ignorePipeSignal() {
        if(signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
            std::cerr << "Error ignoring signal..\n";
        }
    }
    
    bool convertHostToIp(const std::string &hostname , std::string &ip)
    {
        struct hostent *he;
        struct in_addr **addr_list;
        int i;
        if ((he = gethostbyname( hostname.c_str())) == NULL)
        {
            herror("gethostbyname");
            return false;
        }
        addr_list = (struct in_addr **) he->h_addr_list;
        for(i = 0; addr_list[i] != NULL; i++)
        {
            ip = inet_ntoa(*addr_list[i]);
            return true;
        }
        return false;
    }
}
