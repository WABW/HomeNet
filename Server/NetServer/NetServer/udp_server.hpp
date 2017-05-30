//
//  udp_server.hpp
//  NetServer
//
//  Created by Cirno MainasuK on 2017-5-29.
//  Copyright © 2017年 Cirno MainasuK. All rights reserved.
//

#ifndef udp_server_hpp
#define udp_server_hpp

extern "C" {
#include "console_print.h"
#include "device_descriptor.h"
}

#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include <event.h>

#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "server_context.h"
#include "shunter.hpp"

class UDPServer {

private:
    int port;

    static void read_event(struct bufferevent *bev, void *ctx);
    static void error_event(struct bufferevent *bev, short error, void *ctx);
    static void sock_accept(evutil_socket_t listener, short event, void *arg);


public:
    UDPServer(int port);
    void run(struct event_base *base);
};

#endif /* udp_server_hpp */
