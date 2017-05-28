//
//  device_descriptor.h
//  NetServer
//
//  Created by Cirno MainasuK on 2017-5-28.
//  Copyright © 2017年 Cirno MainasuK. All rights reserved.
//

#ifndef device_descriptor_h
#define device_descriptor_h

#include <stdio.h>
#include <sys/socket.h>

#define ID_LEN      5

enum {
    ID_sensor = 1,
    ID_alarm,
    ID_server,
    ID_web
};

typedef struct device_descriptor {
    char id[ID_LEN + 1];
    struct sockaddr_storage ss;
} *Device_Descriptor;

#endif /* device_descriptor_h */
