//
//  main.cpp
//  NetServer
//
//  Created by Cirno MainasuK on 2017-5-25.
//  Copyright © 2017年 Cirno MainasuK. All rights reserved.
//

#include <iostream>
#include <map>

#include "tcp_server.hpp"

int main(int argc, const char * argv[]) {
    struct event_base *base = event_base_new();
    int port = 6666;

    Shunter shunter;
    AlarmService as;
    TemperatureService ts(as);

    shunter.addService(ID_alarm, &as);
    shunter.addService(ID_sensor, &ts);

    TCPServer tcpServer(shunter, port);
    tcpServer.run(base);

    return 0;
}
