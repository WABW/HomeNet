//
//  console_print.c
//  NetServer
//
//  Created by Cirno MainasuK on 2017-5-28.
//  Copyright © 2017年 Cirno MainasuK. All rights reserved.
//

#include "console_print.h"

void consolePrint(const char *fmt, ...) {
#ifdef DEBUG
    va_list arg_ptr;
    va_start(arg_ptr, fmt);
    vfprintf(stderr, fmt, arg_ptr);
    va_end(arg_ptr);
#endif
}
