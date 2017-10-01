#include"socket.hpp"
#include<fstream>
#include<sstream>


void extract_url(const std::string &url, std::string &site_url, std::string &path) {
    auto pos = url.find("http://");
    std::string url_right = url.substr(pos+7, url.length()-7);
    auto pos2 = url_right.find("/");
    if(pos2 != std::string::npos) {
        site_url = url_right.substr(0, pos2);
        path = url_right.substr(pos2+1, url_right.length()-pos2);
        if(path[path.length()-1] == '/')
            path = path.substr(0, path.length()-1);
    } else {
        site_url = url_right;
        path = "/";
    }
}

int convertHostToIp(const std::string &hostname , std::string &ip)
{
    struct hostent *he;
    struct in_addr **addr_list;
    int i;
    if ((he = gethostbyname( hostname.c_str())) == NULL)
    {
        herror("gethostbyname");
        return 1;
    }
    addr_list = (struct in_addr **) he->h_addr_list;
    for(i = 0; addr_list[i] != NULL; i++)
    {
        ip = inet_ntoa(*addr_list[i]);
        return 0;
    }
    return 1;
}

int main(int argc, char **argv) {
    if(argc != 2) {
        std::cerr << "Error requires on argument file to download.\n";
        exit(EXIT_FAILURE);
    }
    std::string url = argv[1];
    auto pos = url.find("http://");
    if(pos == std::string::npos) {
        std::cerr << "Only supports http\n";
        exit(EXIT_FAILURE);
    }
    std::string site_url, path;
    extract_url(url, site_url, path);
    net::Socket sock;
    std::cout << "Connecting to: " << site_url << " port 80\n";
    std::string host_ip;
    convertHostToIp(site_url, host_ip);
    std::cout << "IP Resolved to: " << host_ip << "\n";
    if(sock.connectToHost(host_ip,"80", net::SocketType::STREAM) != -1) {
        std::string send_str = "GET /";
        send_str += path + " HTTP/1.0\n\n";
        sock.sendString(send_str);
        std::fstream file;
        auto t = path.rfind("/");
        std::string filename;
        if(t == std::string::npos) {
            filename = path;
        } else {
        	filename = path.substr(t+1, path.length()-t);
        }
        file.open(filename, std::ios::out | std::ios::binary);
        if(!file.is_open()) {
            std::cerr << "Couldn't open: " << filename << " for writing!\n";
            exit(EXIT_FAILURE);
        }
        std::cout << "Saving file: " << filename << "\n";
        while(1) {
            char buffer[1024*8];
            ssize_t len = sock.receive(buffer, 1024*8);
            if(len == 0) break;
            file.write(buffer, len);
        }
        file.close();
        sock.closeSocket();
    } else {
        herror("connect");
        std::cerr << "Error could not connect to host: " << site_url << "\n";
    }
	return 0;
}
