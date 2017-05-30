//
//  alarm_service.hpp
//  NetServer
//
//  Created by Cirno MainasuK on 2017-5-29.
//  Copyright © 2017年 Cirno MainasuK. All rights reserved.
//

#ifndef alarm_service_hpp
#define alarm_service_hpp

extern "C" {
#include "device_descriptor.h"
}

#include <string>
#include <list>

#include "service.h"

class AlarmService final : public Service  {

public:
    std::string receive(std::string line, Device_Descriptor dd) const override;
    void alarm(bool isOn) const;
    
};

#endif /* alarm_service_hpp */
