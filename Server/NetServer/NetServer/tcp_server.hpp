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

class TCPServer {

private:
    Shunter shunter;
    int port;

public:
    TCPServer(Shunter shunter, int port);
    void run(struct event_base *base);
    void read_event(struct bufferevent *bev, Device_Descriptor dd);
    void error_event(struct bufferevent *bev, short error, Device_Descriptor dd);
    void accept_event(Device_Descriptor dd);
};

#endif /* tcp_server_hpp */
