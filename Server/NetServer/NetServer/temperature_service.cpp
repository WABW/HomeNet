//
//  temperature_service.cpp
//  NetServer
//
//  Created by Cirno MainasuK on 2017-5-29.
//  Copyright © 2017年 Cirno MainasuK. All rights reserved.
//

#include "temperature_service.hpp"

TemperatureService::TemperatureService(AlarmService alarmService) {
    this->alarmService = alarmService;
}

std::string TemperatureService::receive(std::string line, Device_Descriptor dd) const {

    if (isAck(line)) {

    } else {

    }

    return "";
}

void TemperatureService::alarm(bool isOn) const {
    alarmService.alarm(isOn);
}

bool TemperatureService::isAck(std::string line) const {
    return ('A' == line[1]) ? true : false;
}
