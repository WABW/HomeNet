//
//  tcp_server.cpp
//  NetServer
//
//  Created by Cirno MainasuK on 2017-5-28.
//  Copyright © 2017年 Cirno MainasuK. All rights reserved.
//

#include "tcp_server.hpp"

#define MAX_LINE    16384

TCPServer::TCPServer(int port) {
    this->port = port;
}

/**
  read callback
**/
void TCPServer::read_event(struct bufferevent *bev, void *ctx) {
    struct evbuffer *input, *output;
    char *line;
    size_t n;

    input = bufferevent_get_input(bev);
    output = bufferevent_get_output(bev);

    while ((line = evbuffer_readln(input, &n, EVBUFFER_EOL_LF))) {
        evbuffer_add(output, line, n);
        evbuffer_add(output, "\n", 1);

        // Debug
        fprintf(stderr, "%s\n", line);

        free(line);
    }
}

/** 
  Error callback
**/
void TCPServer::error_event(struct bufferevent *bev, short error, void *ctx) {
    Device_Descriptor dd = (Device_Descriptor) ctx;
    assert(NULL != dd);

    struct sockaddr_in *sin = (sockaddr_in *) &(dd->ss);

    consolePrint("%s[%s:%d] %s:",
                 dd->id,
                 inet_ntoa(sin->sin_addr),
                 (int) ntohs(sin->sin_port),
                 evutil_socket_error_to_string(EVUTIL_SOCKET_ERROR()));

    if (error & BEV_EVENT_EOF) {
        // client close connect
        consolePrint(" (EOF)\n");
    } else if (error & BEV_EVENT_ERROR) {
        // chekc errno to see what error occurred
        // client send RST
        consolePrint(" (EVENT)\n");
    } else if (error & BEV_EVENT_TIMEOUT) {
        // handle timeout event here
        consolePrint(" (TIMEOUT)\n");
    }

    bufferevent_free(bev);
}

void TCPServer::sock_accept(evutil_socket_t listenser, short event, void *arg) {
    struct event_base *base = (struct event_base *) arg;
    struct sockaddr_storage ss;
    socklen_t slen = sizeof(ss);

    int fd = accept(listenser, (struct sockaddr *) &ss, &slen);

    if (fd < 0) {
        perror("accept");
    } else if (fd > FD_SETSIZE) {
        close(fd);
    } else {
        struct bufferevent *bev;
        Device_Descriptor dd = (Device_Descriptor) malloc(sizeof(struct device_descriptor));

        strcpy(dd->id, "10001");
        dd->ss = ss;

        evutil_make_socket_nonblocking(fd);
        bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
        bufferevent_setcb(bev, read_event, NULL, error_event, dd);
        bufferevent_setwatermark(bev, EV_READ, 0, MAX_LINE);
        bufferevent_enable(bev, EV_READ | EV_WRITE);
    }
}

void TCPServer::run(struct event_base *base) {
    assert(NULL != base);

    evutil_socket_t listener;

    struct sockaddr_in sin;
    struct event *listener_event;

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(this->port);

    listener = socket(AF_INET, SOCK_STREAM, 0);
    evutil_make_socket_nonblocking(listener);

    if (bind(listener, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("bind");
        return ;
    }

    if (listen(listener, 16) < 0) {
        perror("listen");
        return ;
    }
    // EV_READ: Persistent event: won't get removed automatically when activated.
    // EV_PERSIST: Persistent event: won't get removed automatically when activated.
    listener_event = event_new(base, listener, EV_READ | EV_PERSIST, sock_accept, (void *)base);

    // Add an event to the set of pending events.
    event_add(listener_event, NULL);
    // Make an event active.
    event_base_dispatch(base);
}
