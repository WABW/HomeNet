//
//  tcp_server.hpp
//  NetServer
//
//  Created by Cirno MainasuK on 2017-5-28.
//  Copyright © 2017年 Cirno MainasuK. All rights reserved.
//

#ifndef tcp_server_hpp
#define tcp_server_hpp

extern "C" {
#include "console_print.h"
#include "device_descriptor.h"
}

#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <event.h>

#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <event.h>

class TCPServer {

private:
    int port;

    static void read_event(struct bufferevent *bev, void *ctx);
    static void error_event(struct bufferevent *bev, short error, void *ctx);
    static void sock_accept(evutil_socket_t listener, short event, void *arg);


public:
    TCPServer(int port);
    void run(struct event_base *base);
};

#endif /* tcp_server_hpp */
