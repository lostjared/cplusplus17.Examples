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
    if(net::convertHostToIp(site_url, host_ip) == false) {
        std::cerr << "Could not convert to IP address.\n";
        exit(EXIT_FAILURE);
    }
    std::cout << "IP Resolved to: " << host_ip << "\n";
    if(sock.connectToHost(host_ip,"80", net::SocketType::STREAM) != -1) {
        std::ostringstream stream;
        stream << "GET /" << path << " HTTP/1.1\r\nHost: "<<site_url<<"\r\n\r\n";
        sock.sendString(stream.str());
        std::cout << "GET /" << path << " HTTP/1.1\r\nHost: " << site_url << "\n";
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
        std::string text;
        if(sock.readHeader(text) == -1) {
            herror("read");
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
