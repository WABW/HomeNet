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

#define ID_LEN      15

enum Device_Type {
    ID_none,
    ID_sensor = 'C',
    ID_alarm = 'B',
    ID_server = 'F',
    ID_web = 'W'
};

typedef struct device_descriptor {
    char id[ID_LEN + 1];
    struct sockaddr_storage ss;
    size_t tick;
} *Device_Descriptor;

#endif /* device_descriptor_h */
