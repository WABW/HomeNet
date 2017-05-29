//
//  shunter.hpp
//  NetServer
//
//  Created by Cirno MainasuK on 2017-5-29.
//  Copyright © 2017年 Cirno MainasuK. All rights reserved.
//

#ifndef shunter_hpp
#define shunter_hpp

extern "C" {
#include "console_print.h"
#include "device_descriptor.h"
}

#include <string>
#include <map>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include "temperature_service.hpp"

class Shunter {

public:
    std::string shunt(std::string line, Device_Descriptor dd);
    bool addService(Device_Type key, Service *service);

private:
    std::map<Device_Type, Service *> serviceMap;
    Device_Type type(std::string);

};

#endif /* shunter_hpp */
