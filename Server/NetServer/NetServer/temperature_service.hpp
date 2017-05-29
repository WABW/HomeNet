//
//  temperature_service.hpp
//  NetServer
//
//  Created by Cirno MainasuK on 2017-5-29.
//  Copyright © 2017年 Cirno MainasuK. All rights reserved.
//

#ifndef temperature_service_hpp
#define temperature_service_hpp

extern "C" {
#include "device_descriptor.h"
}

#include <string>
#include "alarm_service.hpp"

class TemperatureService final : public Service {

public:
    TemperatureService(AlarmService alarmService);
    std::string receive(std::string line, Device_Descriptor dd) const override;

private:
    AlarmService alarmService;

    void alarm(bool isOn) const;
    bool isAck(std::string) const;

};

#endif /* temperature_service_hpp */
