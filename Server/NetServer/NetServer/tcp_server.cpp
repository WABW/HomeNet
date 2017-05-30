//
//  tcp_server.cpp
//  NetServer
//
//  Created by Cirno MainasuK on 2017-5-28.
//  Copyright © 2017年 Cirno MainasuK. All rights reserved.
//

#include "tcp_server.hpp"

namespace {
    size_t MAX_LINE = 16384;

    void read_callback(struct bufferevent *bev, void *ctx) {
        Server_Context sc = (Server_Context) ctx;
        TCPServer *server = static_cast<TCPServer *>(sc->server);

        server->read_event(bev, sc->dd);
    }

    void error_callback(struct bufferevent *bev, short error, void *ctx) {
        Server_Context sc = (Server_Context) ctx;
        TCPServer *server = static_cast<TCPServer *>(sc->server);

        server->error_event(bev, error, sc->dd);
    }

    void sock_callback(evutil_socket_t listener, short event, void *arg) {
        Server_Context sc = (Server_Context) arg;
        TCPServer *server = static_cast<TCPServer *>(sc->server);

        struct sockaddr_storage ss;
        socklen_t slen = sizeof(ss);
        int fd = accept(listener, (struct sockaddr *) &ss, &slen);

        if (fd < 0) {
            perror("accept");
        } else if (fd > FD_SETSIZE) {
            close(fd);
        } else {
            struct bufferevent *bev;
            Device_Descriptor dd = (Device_Descriptor) malloc(sizeof(struct device_descriptor));

            strcpy(dd->id, "Unknown");
            dd->ss = ss;
            dd->tick = 0;

            sc->dd = dd;

            evutil_make_socket_nonblocking(fd);
            bev = bufferevent_socket_new(sc->base, fd, BEV_OPT_CLOSE_ON_FREE);
            bufferevent_setcb(bev, read_callback, NULL, error_callback, sc);
            bufferevent_setwatermark(bev, EV_READ, 0, MAX_LINE);
            bufferevent_enable(bev, EV_READ | EV_WRITE);

            server->accept_event(dd);
        }   // end if
    }

}   // end namespace

TCPServer::TCPServer(Shunter shunter, int port) : shunter(shunter) {
    this->port = port;
}


void TCPServer::read_event(struct bufferevent *bev, Device_Descriptor dd) {
    struct evbuffer *input, *output;
    char *line;
    std::string out;
    size_t n;

    assert(NULL != dd);

    input = bufferevent_get_input(bev);
    output = bufferevent_get_output(bev);

    while ((line = evbuffer_readln(input, &n, EVBUFFER_EOL_LF))) {
        out = shunter.shunt(line, dd);

        if (!out.empty()) {
            evbuffer_add(output, out.c_str(), out.length());
            evbuffer_add(output, "\n", 1);
        }

        free(line);
    }
}

void TCPServer::error_event(struct bufferevent *bev, short error, Device_Descriptor dd) {
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

void TCPServer::accept_event(Device_Descriptor dd) {

}

void TCPServer::run(struct event_base *base) {
    assert(NULL != base);

    Server_Context sc = (Server_Context) malloc(sizeof(struct server_context));

    sc->server = this;
    sc->base = base;
    sc->dd = NULL;

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
    listener_event = event_new(base, listener, EV_READ | EV_PERSIST, sock_callback, (void *)sc);

    // Add an event to the set of pending events.
    event_add(listener_event, NULL);
    // Make an event active.
    event_base_dispatch(base);
}
