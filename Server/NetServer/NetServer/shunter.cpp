//
//  shunter.cpp
//  NetServer
//
//  Created by Cirno MainasuK on 2017-5-29.
//  Copyright © 2017年 Cirno MainasuK. All rights reserved.
//

#include "shunter.hpp"

// MARK: public

std::string Shunter::shunt(std::string line, Device_Descriptor dd) {
    struct sockaddr_in *sin = (sockaddr_in *) &(dd->ss);

    dd->tick += 1;
    consolePrint("%s(%zd)[%s:%d] %s\n",
                 dd->id,
                 dd->tick,
                 inet_ntoa(sin->sin_addr),
                 (int) ntohs(sin->sin_port),
                 line.c_str());


    auto type = this->type(line);
    if (serviceMap.find(type) != serviceMap.end()) {
        return serviceMap.at(type)->receive(line, dd);
    }

    consolePrint("not exist service type\n");
    return "";
}

bool Shunter::addService(Device_Type key, Service *service) {
    return serviceMap.insert(std::make_pair(key, service)).second;
}

// MARK: private

Device_Type Shunter::type(std::string line) {
    return (Device_Type) line[0];
}
