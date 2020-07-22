#include <lclib-c++/Sockets.hpp>

#include <cstdio>
#include <cstdlib>

#include <thread>
#include <mutex>

//const char *socket_path = "wc_connect_sock";


int main(int argc, char** argv) {
    const char* host = "127.0.0.1";
    uint16_t port{};
    std::uint16_t n{};
    std::mutex cout_mtx{};
    if(argc<1){
        std::printf("Usage: %s [host] <port> ",argv[0]);
        return 1;
    }
    else if(argc<2)
        port = std::atoi(argv[1]);
    else{
        port = std::atoi(argv[2]);
        host = argv[1];
    }
    lclib::socket::TcpServer tcpServer{};
    tcpServer.listen(host,port);

    while(true){
        std::thread{[sock=tcpServer.accept(),n=n++,&cout_mtx]()mutable{
            lclib::io::InputStream& in = sock.getInputStream();
            int c;
            while((c = in.read())!=lclib::io::eof)
                putchar(c);
        }}.detach();
    }
}
