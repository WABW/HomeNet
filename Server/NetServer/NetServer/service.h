//
//  service.h
//  NetServer
//
//  Created by Cirno MainasuK on 2017-5-29.
//  Copyright © 2017年 Cirno MainasuK. All rights reserved.
//

#ifndef service_h
#define service_h

class Service {

protected:
    std::list<Device_Descriptor> list = std::list<Device_Descriptor>();

public:
    virtual std::string receive(std::string line, Device_Descriptor dd) const = 0;

};


#endif /* service_h */
