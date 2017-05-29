//
//  server_context.h
//  NetServer
//
//  Created by Cirno MainasuK on 2017-5-29.
//  Copyright © 2017年 Cirno MainasuK. All rights reserved.
//

#ifndef server_context_h
#define server_context_h

#include "device_descriptor.h"

#include "tcp_server.hpp"
#include "udp_server.hpp"

typedef struct server_context {
    void *server;
    struct event_base *base;
    Device_Descriptor dd;
} *Server_Context;

#endif /* server_context_h */
